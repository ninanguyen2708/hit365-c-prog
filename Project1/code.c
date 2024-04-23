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

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR (i, 0, (n))
#define BAC(i, a, b) for (int i = (a - 1); i >= (b); --i)
#define TRACE(x) printf(#x ": %lld\n", (ll)(x))
#define BIT(x, i) (((x) >> (i)) & 1)
#define MASK(i) (1LL << (i))
#define mem(i, a) memset(i, a, sizeof i)
#define el printf("\n")
#define bs printf(" ")
#define f first
#define s second

const int MOD = 998244353; // 1000000007
const ll INF = 1e18;
const int oo = 1000000007;
const int MX = 100001;

ll pw(ll a, ll b, ll m) {
	ll res = 1; a %= m; while (b > 0) { if (b & 1) res = (res * a) % m; a = (a * a) % m; b >>= 1; } 
	return res; 
}
int maximize(ll* a, ll b) { if (*a < b) { *a = b; return 1; } return 0; }
int minimize(ll* a, ll b) { if (*a > b) { *a = b; return 1; } return 0; }

//body
char pc; pid cntPC[5] = { {0, 0} };
double manaSalary, hourlyWage, hours;
double basicSalary, itemA, itemB, itemC, cntA, cntB, cntC;

pd hourly(double sal, double ho) {
	double regular, overtime, newHour;
	newHour = 0; if (ho - 40 > 0) newHour = ho - 40;
	regular = sal * ho; overtime = sal * 1.5 * newHour;
	return (pd) { regular, overtime };
}

void sales(double a, double b, double c, double ans[4]) {
	ans[0] = a * (5.7 / 100);
	ans[1] = b * (6.4 / 100);
	ans[2] = c * (7.2 / 100);
	ans[3] = ans[0] + ans[1] + ans[2];
}

void items(double a, double b, double c, double ans[4]) {
	ans[0] = a * 22.5;
	ans[1] = b * 24.5;
	ans[2] = c * 26;
	ans[3] = ans[0] + ans[1] + ans[2];
}

int main(void) {
	for (;;) {
		printf("Enter employee paycode (1, 2, 3, 4, Q): ");
		scanf_s(" %c", &pc);

		/*manager*/
		if (pc == '1') {
			printf("Enter weekly salary for manager: ");
			scanf_s("%lf", &manaSalary);
			printf("Manager salary of $%.2lf", manaSalary);
			el;
			cntPC[1].first++; cntPC[1].second += manaSalary;
		}

		/*hourly wage*/
		else if (pc == '2') {
			printf("Enter the hourly wage for the employee: ");
			scanf_s("%lf", &hourlyWage);
			printf("Enter hours worked for hourly employee: ");
			scanf_s("%lf", &hours);
			pd res = hourly(hourlyWage, hours); 
			double total = res.first + res.second;
			printf("Wages are $%.2lf ($%.2lf regular and $%.2lf overtime)", total, res.first, res.second);
			el;
			cntPC[2].first++; cntPC[2].second += total;
		}

		/*sales value*/
		else if (pc == '3') {
			printf("Enter the sales value of item A: ");
			scanf_s("%lf", &itemA);
			printf("Enter the sales value of item B: ");
			scanf_s("%lf", &itemB);
			printf("Enter the sales value of item C: ");
			scanf_s("%lf", &itemC);
			basicSalary = 250;
			double res[4], totalCom; sales(itemA, itemB, itemC, res);
			totalCom = basicSalary + res[3];
			printf("Commistion wage is $%.2lf ($%.2lf base + $%.2lf commisions ($%.2lf item A, $%.2lf item B, $%2.lf item C))",
				totalCom, basicSalary, res[3], res[0], res[1], res[2]);
			el;
			cntPC[3].first++; cntPC[3].second += totalCom;
		}

		else if (pc == '4') {
			//items();
			printf("Enter the number produced of item 1: ");
			scanf_s("%lf", &cntA);
			printf("Enter the number produced of item 2: ");
			scanf_s("%lf", &cntB);
			printf("Enter the number produced of item 3: ");
			scanf_s("%lf", &cntC);
			double res[4]; items(cntA, cntB, cntC, res);
			printf("Pieceworker wage: $%.2lf (items 1 $%.2lf, items 2 $%.2lf, items 3 $%.2lf)", res[3], res[0], res[1], res[2]);
			el;
			cntPC[4].first++; cntPC[4].second += res[3];
		}

		else if (pc == 'Q') {
			//total();
			double totalWag = 0;
			int totalEm = 0;
			for (int i = 1; i <= 4; i++) {
				totalEm += cntPC[i].first;
				totalWag += cntPC[i].second;
			}
			printf("Manager: Employees: %d  Total wages: $%.2lf", cntPC[1].first, cntPC[1].second); el;
			printf("Hourly: Employees: %d  Total wages: $%.2lf", cntPC[2].first, cntPC[2].second); el;
			printf("Commision: Employees: %d  Total wages: $%.2lf", cntPC[3].first, cntPC[3].second); el;
			printf("Pieceworker: Employees: %d  Total wages: $%.2lf", cntPC[4].first, cntPC[4].second); el;
			printf("Net Total: Employees: %d  Total wages: $%.2lf", totalEm, totalWag); el;
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

