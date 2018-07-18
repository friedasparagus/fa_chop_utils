#include "chop_constraints.h"

function vector chfetch(const int input, idx, sample)
{
	int	chn=idx*3;

	vector vec = set(
		chinput(input, chn+0, sample),
		chinput(input, chn+1, sample),
		chinput(input, chn+2, sample)
	);

	return vec;
}

function vector chfetch(const int input, idx, sample, use_offset)
{
	int chn=idx;
	if(use_offset>0)
		chn=idx*3;

	vector vec = set(
		chinput(input, chn+0, sample),
		chinput(input, chn+1, sample),
		chinput(input, chn+2, sample)
	);

	return vec;
}

function vector chfetch(const int input; const string name; const int sample)
{
	int chn=chindex(input, name + "x");

	vector vec = set(
		chinput(input, chn+0, sample),
		chinput(input, chn+1, sample),
		chinput(input, chn+2, sample)
	);

	return vec;
}

function matrix chfetch(const int input, idx, sample)
{
	int chn=idx*9;

	vector t = chfetch(input, chn+0, sample, -1);
	vector r = chfetch(input, chn+3, sample, -1);
	vector s = chfetch(input, chn+6, sample, -1);
	
	return maketransform(0,0,t,r,s);
}

function matrix chfetch(const int input; string objname; int sample)
{
	int chn=chindex(input, objname + ":tx");

	vector t = chfetch(input, chn+0, sample, -1);
	vector r = chfetch(input, chn+3, sample, -1);
	vector s = chfetch(input, chn+6, sample, -1);
	
	return maketransform(0,0,t,r,s);
}

function chopTRS chfetch(const int input, idx, sample)
{
	chopTRS result;

	int chn=idx*9;

	result.t = chfetch(input, chn+0, sample, -1);
	result.r = chfetch(input, chn+3, sample, -1);
	result.s = chfetch(input, chn+6, sample, -1);

	return result;
}

function chopTRS chfetch(const int input; const string name; const int sample)
{
	chopTRS result;

	int chn=chindex(input, name + ":tx");

	result.t = chfetch(input, chn+0, sample, -1);
	result.r = chfetch(input, chn+3, sample, -1);
	result.s = chfetch(input, chn+6, sample, -1);

	return result;
}
