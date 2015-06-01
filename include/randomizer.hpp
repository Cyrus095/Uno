#pragma once

/*-----------------------------------------------------------*
 *
 *  Functions that generate pseudo-random values of a certain
 *  type.
 *
 */

/*
 *  Returns an integer x, in which a <= x < b.
 *  If called with a > b, throws an exception.
 */
int randInt(int a, int b);
