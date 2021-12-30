#!/bin/bash

# Creator: VPR
# Created: December 29th, 2021
# Updated: December 29th, 2021

# This script is intended to work with Pidjeon for a seamless injection process.

TARGET="HitmanBloodMoney.exe"      # Change as necessary
PAYLOAD="Bin/Release/Shitman3.dll" # Change as necessary
PIDJEON_PATH="${HOME}/.toolkit"    # Change as necessary

export PATH=$PATH:"${PIDJEON_PATH}"

function inject {
    pidjeon_x86.exe "${TARGET}" "${PAYLOAD}" -d 2500
}

inject
