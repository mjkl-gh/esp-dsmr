Import("env")
import os
import re
import shutil

OUTPUT_DIR = "build{}".format(os.path.sep)

def bin_copy(source, target, env):

    platform = env["PIOENV"]

    # convert . to _ so Windows doesn't complain
    variant = "ESP-DSMR-" +  platform.replace(".", "_")
    
    # check if output directories exist and create if necessary
    if not os.path.isdir(OUTPUT_DIR):
        os.mkdir(OUTPUT_DIR)

    for d in ['firmware']:
        if not os.path.isdir("{}{}".format(OUTPUT_DIR, d)):
            os.mkdir("{}{}".format(OUTPUT_DIR, d))

    # create string with location and file names based on variant
    bin_file = "{}firmware{}{}.bin".format(OUTPUT_DIR, os.path.sep, variant)

    # check if new target files exist and remove if necessary
    for f in [bin_file]:
        if os.path.isfile(f):
            os.remove(f)

    print("renaming file to "+bin_file)

    # copy firmware.bin to firmware/<variant>.bin
    shutil.copy(str(target[0]), bin_file)
    print("Done")

env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", [bin_copy])

