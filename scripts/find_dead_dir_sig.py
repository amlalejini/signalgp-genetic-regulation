import os, argparse, csv

def extract_settings(run_config_path):
    content = None
    with open(run_config_path, "r") as fp:
        content = fp.read().strip().split("\n")
    header = content[0].split(",")
    header_lu = {header[i].strip():i for i in range(0, len(header))}
    content = content[1:]
    configs = [l for l in csv.reader(content, quotechar='"', delimiter=',', quoting=csv.QUOTE_ALL, skipinitialspace=True)]
    return {param[header_lu["parameter"]]:param[header_lu["value"]] for param in configs}

# this function is specific to directional signal task
def extract_runlog(fpath):
    content = None
    # Open run.log, grab contents.
    with open(fpath, "r") as fp:
        content = fp.read().strip()
    content = content.split("\n")
    # For each line in the log, collect printed updata/best scores
    values = []
    for line in content:
        if line[:6] == "update":
            line = line.split(";")
            update = int(line[0].split(":")[-1].strip())
            score = float(line[1].split(":")[-1].strip())
            solution = bool(int(line[3].split(":")[-1].strip()))
            values.append({"update":update, "score": score, "solution": solution})
    return values

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Data aggregation script.")
    parser.add_argument("--data", type=str, nargs="+", help="Where should we pull data (one or more locations)?")
    # parser.add_argument("--max_update", type=int, help="Final update for these runs?")
    args = parser.parse_args()
    data_dirs = args.data
    # Are all data directories for real?
    if any([not os.path.exists(loc) for loc in data_dirs]):
        print("Unable to locate all data directories. Able to locate:", {loc: os.path.exists(loc) for loc in data_dirs})
        exit(-1)
    # Aggregate a list of all runs
    run_dirs = [os.path.join(data_dir, run_dir) for data_dir in data_dirs for run_dir in os.listdir(data_dir) if "__SEED_" in run_dir]
    # sort run directories by seed to make easier on the eyes
    run_dirs.sort(key=lambda x : int(x.split("_")[-1]))
    print(f"Found {len(run_dirs)} run directories.")
    dead_seeds = []
    finished_seeds = []
    for run in run_dirs:
        print(f"Extracting from {run}")
        run_config_path = os.path.join(run, "output", "run_config.csv")
        if not os.path.exists(run_config_path):
            print(f"Failed to find run parameters ({run_config_path})")
            exit(-1)
        run_log_path = os.path.join(run, "run.log")
        if not os.path.exists(run_log_path):
            print(f"Failed to find run.log ({run_log_path})")
            exit(-1)
        # Extract run settings.
        run_settings = extract_settings(run_config_path)
        # Extract fitness over time information from run log
        run_seed = run_settings["SEED"]
        expected_final_update = int(run_settings["GENERATIONS"])
        logs = extract_runlog(run_log_path)
        final_update = logs[-1]["update"]
        found_solution = logs[-1]["solution"]
        if found_solution or final_update == expected_final_update:
            finished_seeds.append(run_seed)
        else:
            dead_seeds.append(run_seed)
    print(f"Finished jobs ({len(finished_seeds)}): {str(finished_seeds)}")
    print(f"Dead jobs ({len(dead_seeds)}): {str(dead_seeds)}")
