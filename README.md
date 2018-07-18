# fa_chop_utils
Library of Utility Functions for CHOPs

## chfetch.h
Currently contains definitions for various protoypes of the chfetch function which extends some of the functionality of similar functions found in the "chop_constraints.h" vex header file shipped with Houdini 16.0+.

The primary motivation for extending the existing chopConstraintContext methods 'fetchInput' and 'fetchInputMatrix' is that we are currently unable to specify an 'offset_index' (if we wished to query the next matrix to our current iteration, for example) or a specific point in time at which to evaluate it (query the current matrix at the next sample). This header file attempts to fill the gap.

Supported return types are vector, matrix and chopTRS.

Each of these types can be looked up by channel index or by channel name.

```
vector t = chfetch(input_num, ch_offset, sample_number);
matrix m = chfetch(input_num, ch_offset, sample_number);
chopTRS trs = chfetch(input_num, ch_offset, sample_numner);

vector t = chfetch(input_num, vec_name, sample_number);
matrix m = chfetch(input_num, mat_name, sample_number);
chopTRS trs = chfetch(input_num, trs_name, sample_number);
```

where `input_num` is the zero-indexed input number to be queried.

`ch_offset` is the zero-indexed 'address' of the instance we want to fetch - for example, if our first input is a set of 9 translate/rotate/scale channels then we can grab the translate vector at the current sample with:

```vector t = chfetch(0, 0, I);```

rotate with:
```vector r = chfetch(0, 1, I);```

and scale with:
```vector s = chfetch(0, 2, I);```

These elements are already easily queried via the chopTRS struct included with Houdini. However if our input channels are merely a set of arbitrary vectors, and not complete transforms, then we'd be stuck with boilerplating this behaviour.

When querying by name the functions try to adhere to current naming conventions within Houdini.

For vectors the given name will be appended with "x", so:
`vector biff = chfetch(0, "t", I)` will set 'biff' to the value of the channel connected to the first input named "tx" and that of the next two channels.

For matrices the given name with be appended with ":tx" (this is a possible candidate for revision). The same is true for returning a chopTRS struct:

`matrix null1 = chfetch(0, "/obj/null1", I);` will fetch the channel named "/obj/null1:tx" and the following 8 channels before building the matrix.
