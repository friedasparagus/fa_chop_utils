# fa_chop_utils
Library of Utility Functions for CHOPs

## chfetch.h
Currently contains definitions for various protoypes of the chfetch function which extends some of the functionality of similar functions found in the "chop_constraints.h" vex header file shipped with Houdini 16.0+.

The primary motivation for extending the existing chopConstraintContext methods 'fetchInput' and 'fetchInputMatrix' is that we are currently unable to specify an 'offset_index' (if we wished to query the next matrix to our current iteration, for example) or a specific point in time at which to evaluate it (query the current matrix at the next sample). This header file attempts to fill the gap.
