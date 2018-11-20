#include <gtest/gtest.h>
#include <tuple>
#include <vector>
#include "LAutomataBuilder.h"

class Tester :public ::testing::Test {
public:
 	static void SetUpTestCase();
    static std::vector<std::tuple<int, char ,int>> GetElement(size_t index);
    static void SetUpAutomata();

	static std::vector<std::vector<std::tuple<int, char ,int>>> correct_automatas;
	static std::vector<LAutomata*> automatas;
};