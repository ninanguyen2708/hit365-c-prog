#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ___ << " 3 " >>

typedef long long ll;
typedef long double ld;
typedef struct { int first; double second; } pid;
typedef struct { double first; double second; } pd;

#define el printf("\n")
#define bs printf(" ")

//body
char pc; pid cntPC[5] = { {0, 0} };
double manaSalary, hourlyWage, hours;
double basicSalary, itemA, itemB, itemC, cntA, cntB, cntC;
int totalEm;
ld totalWage;

pd hourly(double sal, double ho) {
	double regular, overtime, newHour;
	newHour = 0; 

	if (ho - 40 > 0) newHour = ho - 40, ho = 40;

	regular = sal * ho; overtime = sal * 1.5 * newHour;
	return (pd) { regular, overtime };
}

void sales(double a, double b, double c, double ans[4]) {
	ans[0] = a * (double)(5.7 / 100);
	ans[1] = b * (double)(6.4 / 100);
	ans[2] = c * (double)(7.2 / 100);
	ans[3] = ans[0] + ans[1] + ans[2];
}

void items(double a, double b, double c, double ans[4]) {
	ans[0] = a * 22.5;
	ans[1] = b * 24.5;
	ans[2] = c * 26;
	ans[3] = ans[0] + ans[1] + ans[2];
}

void input(char* s, double* x) {
	while (1) {
		printf(s);
		if (scanf_s("%lf", x) == 1) {
			while (getchar() != '\n');  // clear leftover char
			break;  
		} else {
			while (getchar() != '\n');
		}
	}
}

int main(void) {
	totalEm = 0; totalWage = 0;
	for (;;) {
		printf("Enter employee paycode (1, 2, 3, 4, Q): ");
		scanf_s(" %c", &pc);

		/*manager*/
		if (pc == '1') {
			input("Enter weekly salary for manager: ", &manaSalary);
			printf("Manager salary of $%.2lf", manaSalary);
			el;
			cntPC[1].first++; cntPC[1].second += manaSalary;
			totalEm += cntPC[1].first; totalWage += cntPC[1].second;
		}

		/*hourly wage*/
		else if (pc == '2') {
			input("Enter the hourly wage for the employee: ", &hourlyWage);
			//printf("Enter the hourly wage for the employee: ");
			//scanf_s("%lf", &hourlyWage);
			input("Enter hours worked for hourly employee: ", &hours);
			//printf("Enter hours worked for hourly employee: ");
			//scanf_s("%lf", &hours);
			pd res = hourly(hourlyWage, hours); 
			double total = res.first + res.second;
			printf("Wages are $%.2lf ($%.2lf regular and $%.2lf overtime)", total, res.first, res.second);
			el;
			cntPC[2].first++; cntPC[2].second += total;
			totalEm += cntPC[2].first; totalWage += cntPC[2].second;
		}

		/*sales value*/
		else if (pc == '3') {
			input("Enter the sales value of item A: ", &itemA);
			//printf("Enter the sales value of item A: ");
			//scanf_s("%lf", &itemA);
			input("Enter the sales value of item B: ", &itemB);
			//printf("Enter the sales value of item B: ");
			//scanf_s("%lf", &itemB);
			input("Enter the sales value of item C: ", &itemC);
			//printf("Enter the sales value of item C: ");
			//scanf_s("%lf", &itemC);
			basicSalary = 250;
			double res[4], totalCom; sales(itemA, itemB, itemC, res);
			totalCom = basicSalary + res[3];
			printf("Commistion wage is $%.2lf ($%.2lf base + $%.2lf commisions ($%.2lf item A, $%.2lf item B, $%.2lf item C))",
				totalCom, basicSalary, res[3], res[0], res[1], res[2]);
			el;
			cntPC[3].first++; cntPC[3].second += totalCom;
			totalEm += cntPC[3].first; totalWage += cntPC[3].second;
		}

		else if (pc == '4') {
			//items();
			input("Enter the number produced of item 1: ", &cntA);
			//printf("Enter the number produced of item 1: ");
			//scanf_s("%lf", &cntA);
			input("Enter the number produced of item 2: ", &cntB);
			//printf("Enter the number produced of item 2: ");
			//scanf_s("%lf", &cntB);
			input("Enter the number produced of item 3: ", &cntC);
			//printf("Enter the number produced of item 3: ");
			//scanf_s("%lf", &cntC);
			double res[4]; items(cntA, cntB, cntC, res);
			printf("Pieceworker wage: $%.2lf (items 1 $%.2lf, items 2 $%.2lf, items 3 $%.2lf)", res[3], res[0], res[1], res[2]);
			el;
			cntPC[4].first++; cntPC[4].second += res[3];
			totalEm += cntPC[4].first; totalWage += cntPC[4].second;
		}

		else if (pc == 'Q') {
			printf("Manager: Employees: %d  Total wages: $%.2lf", cntPC[1].first, cntPC[1].second); el;
			printf("Hourly: Employees: %d  Total wages: $%.2lf", cntPC[2].first, cntPC[2].second); el;
			printf("Commision: Employees: %d  Total wages: $%.2lf", cntPC[3].first, cntPC[3].second); el;
			printf("Pieceworker: Employees: %d  Total wages: $%.2lf", cntPC[4].first, cntPC[4].second); el;
			printf("Net Total: Employees: %d  Total wages: $%.2lf", totalEm, totalWage); el;
			break;
		}

		else {
			printf("Unrecognised paycode. Please only enter '1' for manager, '2' for hourly, '3' for commision, '4' for pieceworker, or 'Q' to quit and see totals.");
			el;
		}
		el;
	}
	return 0;
}

