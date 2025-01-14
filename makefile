# Define output directory and include directory
OUTPUT_DIR = ./build/objects
INCLUDE_DIR = ./include

# Define the source files
SOURCE_1 = EternityUXModules/removeInputDelay.cpp
SOURCE_2 = EternityUXModules/EdgeRemover.cpp
SOURCE_3 = EternityUXModules/ScriptsManager.cpp

# Define the executables
TARGET_1 = $(OUTPUT_DIR)/remoteInputDelay.exe
TARGET_2 = $(OUTPUT_DIR)/EdgeRemover.exe
TARGET_3 = $(OUTPUT_DIR)/ScriptsManager.exe

# Default target
all: remoteInputDelay edgeRemover scriptsManager

# Build remoteInputDelay
remoteInputDelay: $(SOURCE_1)
	@echo "Building removeInputDelay..."
	g++ -I$(INCLUDE_DIR) $(SOURCE_1) -o $(TARGET_1) -mwindows
	@echo " - you can find removeInputDelay.exe at $(OUTPUT_DIR)."

# Build EdgeRemover
edgeRemover: $(SOURCE_2)
	@echo "Building EdgeRemover..."
	g++ -I$(INCLUDE_DIR) $(SOURCE_2) -o $(TARGET_2) -mwindows
	@echo " - you can find EdgeRemover.exe at $(OUTPUT_DIR)."

# Build ScriptsManager
scriptsManager: $(SOURCE_3)
	@echo "Building ScriptsManager..."
	g++ -I$(INCLUDE_DIR) $(SOURCE_3) -o $(TARGET_3)
	@echo " - you can find ScriptsManager.exe at $(OUTPUT_DIR)."

# Clean the build directory
clean:
	rm -f $(OUTPUT_DIR)/*

.PHONY: all clean remoteInputDelay edgeRemover scriptsManager