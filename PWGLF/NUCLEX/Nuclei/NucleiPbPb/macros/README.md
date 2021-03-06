# Usage of the macros

## Requirements
Before running the macros make sure to have:
- the output file obtained running the task on the data,
- the output file obtained running the task on the MC,
- a working _ROOT6_ installation.

> The names of the output files can be set in the ``Common.h`` header file.

## Walkthrough
Once that the task ran on the trains make sure that the names of the lists generated by the task are corrected in the ``Common.h`` header.
There is a special order to execute the macros you find in this directory. Everything (I hope) you need to do after running the task is executing:
1. ``Signal.C``: it extracts the signal from the data information.
2. ``Efficiency.C``: it extracts all the information about the tracking efficiency times the acceptance.
3. ``Secondaries.C``: this macro computes the correction for the nuclei coming from the material of the beam-pip
4. ``Spectra.C``: this macro takes the output of the first three macros to compute the spectra for each bin of $$p_{T}$$ for all the different cuts.
5. ``Systematics.C``: as the name says, it computes the systematic uncertainties of the measurement.
6. ``Final.C``: it just puts the pieces together making the final spectra plots.

I decided to use multiple macros to better track changes and to ease the debug. Each of these macros generate an output file that can (must?) be checked before running the following steps.

> **Be careful**: by default all the output files of the macros will be saved in the ``/tmp/`` directory in order to keep the working directory clean. You can change the base directory for ROOT files in ``Common.h``.

## Documentation
The documentation is only partially implemented, there are plans to complete it in the future (let's see..)
