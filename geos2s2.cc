/*
 * geos2s2.cc
 *
 *  Created on: Jun 13, 2014
 *      Author: kotaimen
 */

#include <stdio.h>
#include <stdarg.h>

#include <iostream>

#include <geos_c.h>

#include "s2.h"
#include "s2latlng.h"
#include "s2cellid.h"


using namespace std;

void geos_error(const char *fmt, ...) {
	va_list argptr;
	va_start(argptr, fmt);
	vfprintf(stderr, fmt, argptr);
	va_end(argptr);
}

void do_something(GEOSContextHandle_t handle, GEOSGeometry *geom) {

	const GEOSCoordSequence *seq = GEOSGeom_getCoordSeq_r(handle, geom);

	double x, y;
	unsigned i, s;

	GEOSCoordSeq_getSize_r(handle, seq, &s);

	for (i = 0; i < s; ++i) {
		GEOSCoordSeq_getX_r(handle, seq, i, &x);
		GEOSCoordSeq_getX_r(handle, seq, i, &y);

		printf("%f,%f\n", x, y);

		S2LatLng latlng = S2LatLng::FromDegrees(y, x);

		cout << latlng.ToStringInDegrees() << endl;

		S2CellId cell_id = S2CellId::FromLatLng(latlng);
		cout << cell_id.ToString() << endl;
		cout << cell_id.ToToken() << endl;

	}
}

int main(int argc, const char **argv) {
	GEOSContextHandle_t handle = initGEOS_r(geos_error, geos_error);

	GEOSGeometry *geom = GEOSGeomFromWKT_r(handle, "LINESTRING(1 1, 2 2, 3 3)");

	do_something(handle, geom);

	GEOSGeom_destroy_r(handle, geom);

	finishGEOS_r(handle);
	return 0;
}
