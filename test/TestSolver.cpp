#include <gtest/gtest.h>
#include "Solver.h"

TEST(Solver, PositiveNos) {
	//ab+c.aba.*.bac.+.+*
	//babc
	EXPECT_EQ(0, solve("babc", "ab+c.aba.*.bac.+.+*"));
	//acb..bab.c.*.ab.ba.+.+*a.
	//abbaa
	EXPECT_EQ(0, solve("abbaa", "acb..bab.c.*.ab.ba.+.+*a."));
	//ab+*
	//abbbba
	EXPECT_EQ(0, solve("abbbba", "ab+*"));
}
