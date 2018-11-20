#include "LAutomataBuilder.h"

using namespace std;


//Функция которая печатает сообщение об ошибке
//в неблагоприятном случае работы со стеком
//(неправильное регулярное выражение)
void ERROR() { 
	std::cout << "ERROR";
	exit(1);
};

LAutomata* LAutomataBuilder::build(const string& regular_exp) {
	stack<LAutomata*> S;	//Заводм Стек
	for (int i = 0; i < regular_exp.length(); ++i) {			//Пробегаемся по регулярке
		if (regular_exp[i] >= 'a' && regular_exp[i] <= 'z') { 	//Если встретили букву
			LAutomata* A2 = new LAutomata(regular_exp[i]);		//то кладем автомат,
			S.push(A2);											//задающий язык из нее на стек
		}
		else if (regular_exp[i] == '+' ) {	//Если "+" - объединяем языки 
			if (S.size() < 2) {
				ERROR();
			}
			LAutomata* first = S.top();
			S.pop();
			LAutomata* second = S.top();
			S.pop();
			*first += *second;
			S.push(first);
		}
		else if (regular_exp[i] == '.' ) {	//Если "+" - объединяем языки 
			if (S.size() < 2) {
				ERROR();
			}

			LAutomata* first = S.top();
			S.pop();
			LAutomata* second = S.top();
			S.pop();
			*first *= *second;
			S.push(first);
		}
		else if (regular_exp[i] == '*' ) {	//Если "*" - Клини
			if (S.size() < 1) {
				ERROR();
			}

			LAutomata* first = S.top();
			S.pop();
			first->CliniStar();
			S.push(first);
		}
		else {
			ERROR();
		}
	}
	if (S.size() > 1) {
		ERROR();
	}
	B2 = S.top();
	return B2;
}