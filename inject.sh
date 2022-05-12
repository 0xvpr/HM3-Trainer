#!/usr/bin/env bash

# Creator:    VPR
# Created:    December 29th, 2021
# Updated:    May 11, 2022

# This script is intended to work with Pidjeon for a seamless injection process.

TARGET="HitmanBloodMoney.exe"    # Change as necessary
PAYLOAD="Lib/shitman3.dll"       # Change as necessary
#PIDJEON_PATH="${HOME}/.toolkit" # Change as necessary

#export PATH=$PATH:"${PIDJEON_PATH}"

function inject {
    vpr-pidjeon-x86 "${TARGET}" "${PAYLOAD}" -d 2500 -i ManualMap
}

inject
