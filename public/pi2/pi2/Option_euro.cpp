#pragma once
#include "stdafx.h"
#include "Option_euro.h"

using namespace std;

Option_euro::Option_euro() {
	vector<Data> _sample;
	sample=_sample;
}

Option_euro::Option_euro(const Option_euro &G) {
	sample = G.sample;
}

Option_euro::~Option_euro() {
}