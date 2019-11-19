#ifndef ALT_SIGNAL_WORLD_CONFIG_H
#define ALT_SIGNAL_WORLD_CONFIG_H

#include "config/config.h"

EMP_BUILD_CONFIG(AltSignalConfig,
  GROUP(DEFAULT_GROUP, "General settings"),
    VALUE(SEED, int, 0, "Random number seed (-1 for seed based on time)"),
    VALUE(GENERATIONS, size_t, 100, "How many generations do we evolve things?"),
    VALUE(POP_SIZE, size_t, 100, "How big is our population?"),

  GROUP(ENVIRONMENT_GROUP, "Environment settings"),
    VALUE(NUM_SIGNAL_RESPONSES, size_t, 2, "How many responses are there to the environment signal?"),
    VALUE(NUM_ENV_CYCLES, size_t, 8, "How many times does the environment cycle?"),
    VALUE(CPU_TIME_PER_ENV_CYCLE, size_t, 128, "How many CPU steps does a SignalGP organism get during an environment cycle?"),

  GROUP(PROGRAM_GROUP, "Program settings"),
    VALUE(USE_FUNC_REGULATION, bool, true, "Do programs have access to function regulation instructions?"),
    VALUE(USE_GLOBAL_MEMORY, bool, false, "Do programs have access to global memory?"),
    VALUE(MIN_FUNC_CNT, size_t, 0, "Minimum number of functions per program."),
    VALUE(MAX_FUNC_CNT, size_t, 32, "Maximum number of functions per program."),
    VALUE(MIN_FUNC_INST_CNT, size_t, 0, "Minimum number of instructions per function."),
    VALUE(MAX_FUNC_INST_CNT, size_t, 128, "Maximum number of instructions per function."),

  GROUP(HARDWARE_GROUP, "Virtual hardware settings"),
    VALUE(MAX_ACTIVE_THREAD_CNT, size_t, 32, "How many threads can be simultaneously running (active)?"),
    VALUE(MAX_THREAD_CAPACITY, size_t, 64, "Maximum capacity for thread memory (pending + active)."),

  GROUP(SELECTION_GROUP, "Selection settings"),
    VALUE(TOURNAMENT_SIZE, size_t, 7, "How big are tournaments when doing tournament selection?"),

  GROUP(MUTATION_GROUP, "Mutation settings"),
    VALUE(MUT_RATE__INST_ARG_SUB, double, 0.005, "InstArgSub rate"),
    VALUE(MUT_RATE__INST_TAG_BF, double, 0.0005, "InstArgTagBF rate"),
    VALUE(MUT_RATE__INST_SUB, double, 0.005, "InstSub rate"),
    VALUE(MUT_RATE__INST_INS, double, 0.005, "InstIns rate"),
    VALUE(MUT_RATE__INST_DEL, double, 0.005, "InstDel rate"),
    VALUE(MUT_RATE__SEQ_SLIP, double, 0.005, "SeqSlip rate"),
    VALUE(MUT_RATE__FUNC_DUP, double, 0.005, "FuncDup rate"),
    VALUE(MUT_RATE__FUNC_DEL, double, 0.005, "FuncDel rate"),
    VALUE(MUT_RATE__FUNC_TAG_BF, double, 0.0005, "FuncTagBF rate"),

  GROUP(DATA_COLLECTION_GROUP, "Data collection settings"),
    VALUE(SUMMARY_RESOLUTION, size_t, 10, "How often should we output summary statistics?"),
    VALUE(SNAPSHOT_RESOLUTION, size_t, 100, "How often should we snapshot the population?"),
)

#endif