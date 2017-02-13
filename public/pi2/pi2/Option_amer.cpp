#pragma once
#include "stdafx.h"
#include "Option_amer.h"

using namespace std;

Option_amer::Option_amer() {
	vector<Data> _sample;
	sample = _sample;
}

Option_amer::Option_amer(const Option_amer &G) {
	sample = G.sample;
}

Option_amer::~Option_amer() {
}