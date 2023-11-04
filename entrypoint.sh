#!/bin/bash

# Check if the TARGET_APP environment variable is set
if [ -z "$TARGET_APP" ]
then
  echo "TARGET_APP environment variable is not set. Exiting."
  exit 1
fi

# Check if the target executable exists and is executable
if [ -x "/sponge/bin/$TARGET_APP" ]
then
  echo "Running /sponge/bin/$TARGET_APP with arguments: $@"
  /sponge/bin/"$TARGET_APP" "$@" # Execute the target with additional arguments
else
  echo "Target $TARGET_APP does not exist or is not executable. Exiting."
  exit 1
fi