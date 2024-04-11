#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fastVivod2();
void polnaiaOptomizacia();

struct Node
{
	long Vulue;
	struct Node* Left;
	struct Node* Right;
	struct Node* Top;
	long Wight;
};


struct Node* poiskVershins(struct Node* bivshaiaVershina)
{
	if (bivshaiaVershina->Top) return poiskVershins(bivshaiaVershina->Top);
	else return bivshaiaVershina;
}

struct Node* poiskSleduschego(struct Node* ths, char napravlenie)
{
	if (napravlenie)
	{
		if (ths->Left) poiskSleduschego(ths->Left, 1);
		else return ths;
	}
	else
	{
		if (ths->Right) poiskSleduschego(ths->Right, 0);
		else return ths;;
	}
}

long schetMaxUrovnia(long wght)
{
	int maxLevel = 0, vr = 1;
	while (wght > 0)
	{
		wght -= vr;
		maxLevel++;
		vr *= 2;
	}
	return maxLevel;
}

void proverkaMasiva(struct Node* ths)
{
	if (ths)
	{
		if (ths->Left)
		{
			if (ths != ths->Left->Top)
			{
				printf("Error: array is broken");
				exit(41);
			}
			if (ths == ths->Left)
			{
				printf("Error: array is broken (refers to himself)");
				exit(42);
			}
			if (ths->Left->Left)
			{
				if (ths == ths->Left->Left)
				{
					printf("Error: array is broken (refers to himself through one)");
					exit(43);
				}
			}
			if (ths->Left->Right)
			{
				if (ths == ths->Left->Right)
				{
					printf("Error: array is broken (refers to himself through one)");
					exit(43);
				}
			}
			proverkaMasiva(ths->Left);
		}
		if (ths->Right)
		{
			if (ths != ths->Right->Top)
			{
				printf("Error: array is broken");
				exit(41);
			}
			if (ths == ths->Right)
			{
				printf("Error: array is broken (refers to himself)");
				exit(42);
			}
			if (ths->Right->Left)
			{
				if (ths == ths->Right->Left)
				{
					printf("Error: array is broken (refers to himself through one)");
					exit(43);
				}
			}
			if (ths->Right->Right)
			{
				if (ths == ths->Right->Right)
				{
					printf("Error: array is broken (refers to himself through one)");
					exit(43);
				}
			}
			proverkaMasiva(ths->Right);
		}
	}
	else
	{
		printf("Error: where is ths");
		exit(40);
	}
}

long raschotVesa(struct Node* wow)
{
	wow->Wight = 0;
	if (wow->Left) wow->Wight += raschotVesa(wow->Left);
	if (wow->Right) wow->Wight += raschotVesa(wow->Right);
	return (wow->Wight + 1);
}

void optimizacia(struct Node* ths, long level) // "Оптимизирует" дерево
{
	if (!level)
	{
		if (ths->Left && ths->Left->Left && !ths->Right && !ths->Left->Right)
		{
			if (ths->Top)
			{
				if (ths->Top->Left == ths) ths->Top->Left = ths->Left;
				if (ths->Top->Right == ths) ths->Top->Right = ths->Left;
			}
			ths->Left->Right = ths;
			ths->Left->Top = ths->Top;
			ths->Top = ths->Left;
			ths->Left = 0;
			raschotVesa(ths->Top);
		}
		if (ths->Left && ths->Left->Right && !ths->Right && !ths->Left->Left)
		{
			if (ths->Top)
			{
				if (ths->Top->Left == ths) ths->Top->Left = ths->Left->Right;
				if (ths->Top->Right == ths) ths->Top->Right = ths->Left->Right;
			}
			ths->Left->Right->Left = ths->Left;
			ths->Left->Right->Right = ths;
			ths->Left->Right->Top = ths->Top;
			ths->Top = ths->Left->Right;
			ths->Left->Top = ths->Left->Right;
			ths->Left->Right = 0;
			ths->Left = 0;
			raschotVesa(ths->Top);
		}
		if (ths->Right && ths->Right->Right && !ths->Left && !ths->Right->Left)
		{
			if (ths->Top)
			{
				if (ths->Top->Left == ths) ths->Top->Left = ths->Right;
				if (ths->Top->Right == ths) ths->Top->Right = ths->Right;
			}
			ths->Right->Left = ths;
			ths->Right->Top = ths->Top;
			ths->Top = ths->Right;
			ths->Right = 0;
			raschotVesa(ths->Top);
		}
		if (ths->Right && ths->Right->Left && !ths->Left && !ths->Right->Right)
		{
			if (ths->Top)
			{
				if (ths->Top->Left == ths) ths->Top->Left = ths->Right->Left;
				if (ths->Top->Right == ths) ths->Top->Right = ths->Right->Left;
			}
			ths->Right->Left->Right = ths->Right;
			ths->Right->Left->Left = ths;
			ths->Right->Left->Top = ths->Top;
			ths->Top = ths->Right->Left;
			ths->Right->Top = ths->Right->Left;
			ths->Right->Left = 0;
			ths->Right = 0;
			raschotVesa(ths->Top);
		}
		if (ths->Left && ths->Right)
		{
			if (ths->Left->Wight > ths->Right->Wight)
			{
				if (ths->Left->Wight - ths->Right->Wight == 2)
				{
					optimizacia(ths, 1);
				}
			}
			else
			{
				if (ths->Right->Wight - ths->Left->Wight == 2)
				{
					optimizacia(ths, 1);
				}
			}
		}
	}
	else
	{
		if (ths->Left) polnaiaOptomizacia(ths->Left, level - 1);
		if (ths->Right) polnaiaOptomizacia(ths->Right, level - 1);
		if (ths->Left && ths->Right)
		{
			if (ths->Left->Wight - ths->Right->Wight == 2)
			{
				//printf("Nashol v etom otrezke:\n");
				//fastVivod2(ths, 0, 0, samiGluboki(ths, 0), stdout);
				//printf("\n1:\n");
				struct Node* otsuda = poiskSleduschego(ths->Left, 0);
				struct Node* suda = poiskSleduschego(ths->Right, 1);
				if (ths->Top)
				{
					if (ths->Top->Left == ths) ths->Top->Left = otsuda;
					else if (ths->Top->Right == ths)ths->Top->Right = otsuda;
					else exit(33);
				}
				otsuda->Top->Right = otsuda->Left;
				if (otsuda->Left) otsuda->Left->Top = otsuda->Top;
				otsuda->Top = ths->Top;
				ths->Top = suda;
				suda->Left = ths;
				ths->Left->Top = otsuda;
				otsuda->Left = ths->Left;
				otsuda->Right = ths->Right;
				ths->Right->Top = otsuda;
				ths->Left = 0;
				ths->Right = 0;
				proverkaMasiva(otsuda);
				raschotVesa(otsuda);
				//printf("Poluchilos vot eto:\n");
				//fastVivod2(otsuda, 0, 0, samiGluboki(otsuda, 0), stdout);
				optimizacia(otsuda->Left, level - 1);
				//printf("Poluchilos vot eto, posle 1 optimizacii:\n");
				//fastVivod2(otsuda, 0, 0, samiGluboki(otsuda, 0), stdout);
				if (suda->Top) optimizacia(suda->Top, 0);
				//printf("Poluchilos vot eto, posle 2 optimizacii:\n");
				//fastVivod2(otsuda, 0, 0, samiGluboki(otsuda, 0), stdout);
				optimizacia(otsuda->Right, level - 1);
				//printf("Poluchilos vot eto, posle 3 optimizacii:\n");
				//fastVivod2(otsuda, 0, 0, samiGluboki(otsuda, 0), stdout);
			}
			else if (ths->Right->Wight - ths->Left->Wight == 2)
			{
				//printf("Nashol v etom otrezke:\n");
				//fastVivod2(ths, 0, 0, samiGluboki(ths, 0), stdout);
				//printf("\n2:\n");
				struct Node* otsuda = poiskSleduschego(ths->Right, 1);
				struct Node* suda = poiskSleduschego(ths->Left, 0);
				if (ths->Top)
				{
					if (ths->Top->Left == ths) ths->Top->Left = otsuda;
					else if (ths->Top->Right == ths) ths->Top->Right = otsuda;
					else exit(33);
				}
				otsuda->Top->Left = otsuda->Right;
				if (otsuda->Right) otsuda->Right->Top = otsuda->Top;
				otsuda->Top = ths->Top;
				ths->Top = suda;
				suda->Right = ths;
				ths->Right->Top = otsuda;
				otsuda->Right = ths->Right;
				otsuda->Left = ths->Left;
				ths->Left->Top = otsuda;
				ths->Right = 0;
				ths->Left = 0;
				proverkaMasiva(otsuda);
				raschotVesa(otsuda);
				//printf("Poluchilos vot eto:\n");
				//fastVivod2(otsuda, 0, 0, samiGluboki(otsuda, 0), stdout);
				optimizacia(otsuda->Right, level - 1);
				if (suda->Top) optimizacia(suda->Top, 0);
				optimizacia(otsuda->Left, level - 1);
			}
		}
	}

}

void polnaiaOptomizacia(struct Node* ths, long level)
{
	if (level >= 0) optimizacia(ths, level);
	if (ths->Left) polnaiaOptomizacia(ths->Left, level - 1);
	if (ths->Right) polnaiaOptomizacia(ths->Right, level - 1);
}

void dobavka(struct Node* thiis, long chislo, struct Node* neww) // Просто добавляет в дерево
{
	if (thiis)
	{
		if (chislo > thiis->Vulue)
		{
			if (!thiis->Right)
			{
				thiis->Right = neww;
				neww->Top = thiis;
				neww->Vulue = chislo;
				if (thiis->Top) optimizacia(thiis->Top, 0);
			}
			else
			{
				dobavka(thiis->Right, chislo, neww);
			}
		}
		else if (chislo < thiis->Vulue)
		{
			if (!thiis->Left)
			{
				thiis->Left = neww;
				neww->Top = thiis;
				neww->Vulue = chislo;
				if (thiis->Top) optimizacia(thiis->Top, 0);
			}
			else
			{
				dobavka(thiis->Left, chislo, neww);
			}
		}
	}
	else
	{
		printf("Error: the additive object is LOST");
		exit(21);
	}
}

long samiGluboki(struct Node* ths, long samKakoi)
{
	if (ths->Left && ths->Right)
	{
		long Onee;
		long Twoo;
		Onee = samiGluboki(ths->Left, samKakoi + 1);
		Twoo = samiGluboki(ths->Right, samKakoi + 1);
		if (Onee >= Twoo) return Onee;
		else return Twoo;
	}
	else if (ths->Left) return samiGluboki(ths->Left, samKakoi + 1);
	else if (ths->Right) return samiGluboki(ths->Right, samKakoi + 1);
	else return samKakoi;
}

long BlijaishiNePustoi(struct Node* ths, long level, long KolvoPustih, long otNachala, char napravlenie)
{
	if (napravlenie > 0)
	{
		if (ths->Top)
		{
			if (ths->Top->Right)
			{
				if (ths->Top->Right == ths)
				{
					if (ths->Top->Left)
					{
						if (level == 0) return KolvoPustih;
						else return BlijaishiNePustoi(ths->Top->Left, level, KolvoPustih, otNachala, -1);
					}
					else
					{
						if (level == 0) return BlijaishiNePustoi(ths->Top, level + 1, KolvoPustih + 1, otNachala, 1);
						else return BlijaishiNePustoi(ths->Top, level + 1, pow(2, level) + KolvoPustih, otNachala, 1);
					}
				}
				else if (ths->Top->Left)
				{
					if (ths->Top->Left == ths) return BlijaishiNePustoi(ths->Top, level + 1, KolvoPustih, otNachala, 1);
					else
					{
						printf("Error: communication with other elements is broken");
						exit(11);
					}
				}
				else
				{
					printf("Error: communication with other elements is broken");
					exit(11);
				}
			}
			else if (ths->Top->Left)
			{
				if (ths->Top->Left == ths) return BlijaishiNePustoi(ths->Top, level + 1, KolvoPustih, otNachala, 1);
				else
				{
					printf("Error: communication with other elements is broken");
					exit(11);
				}
			}
			else
			{
				printf("Error: communication with other elements is broken");
				exit(11);
			}
		}
		else
		{
			return otNachala + KolvoPustih;
		}
	}
	else
	{
		if (ths->Right)
		{
			if (level == 1) return KolvoPustih;
			else return BlijaishiNePustoi(ths->Right, level - 1, KolvoPustih, otNachala, -1);
		}
		else if (ths->Left)
		{
			if (level == 1) return KolvoPustih + 1;
			else return BlijaishiNePustoi(ths->Left, level - 1, KolvoPustih, otNachala, -1);
		}
		else return BlijaishiNePustoi(ths->Top, level + 1, pow(2, level) + KolvoPustih, otNachala, 1);
	}
}

void fastVivod2(struct Node* thiis, long kolvoProbelov, long strochka, long maxDalni, FILE* fl) // Выводит знаяение и координаты (визуално трудно понять, что за чем идёт)
{
	if (thiis)
	{
		if (thiis->Right) fastVivod2(thiis->Right, kolvoProbelov + 1, strochka + 1, maxDalni, fl);
		else if ((maxDalni - strochka) > 0)
		{
			fastVivod2(0, kolvoProbelov + 1, strochka + 1, maxDalni, fl);
		}
		for (int i = 0; i < kolvoProbelov; i++) fprintf(fl, "          ");
		fprintf(fl, "%d [%d]\n", thiis->Vulue, thiis->Wight);
		if (thiis->Left) fastVivod2(thiis->Left, kolvoProbelov + 1, strochka + 1, maxDalni, fl);
		else if ((maxDalni - strochka) > 0)
		{
			fastVivod2(0, kolvoProbelov + 1, strochka + 1, maxDalni, fl);
		}
	}
	else
	{
		if ((maxDalni - strochka) > 0)
		{
			fastVivod2(0, kolvoProbelov + 1, strochka + 1, maxDalni, fl);
		}
		for (int i = 0; i < kolvoProbelov; i++) fprintf(fl, "          ");
		fprintf(fl, "-- [--]\n");
		if ((maxDalni - strochka) > 0)
		{
			fastVivod2(0, kolvoProbelov + 1, strochka + 1, maxDalni, fl);
		}
	}
}

void fastVivod3(struct Node* ths, long kolvoProbelov, FILE* fl)
{
	if (ths->Right) fastVivod3(ths->Right, kolvoProbelov + 1, fl);
	for (int i = 0; i < kolvoProbelov; i++) fprintf(fl, "      ");
	fprintf(fl, "%d\n", ths->Vulue);
	if (ths->Left) fastVivod3(ths->Left, kolvoProbelov + 1, fl);
}

//void fastVivod1(struct Node* thiis, long kolvoProbelov, long strochka, long maxDalni, FILE* fl) // Выводит знаяение и координаты (визуално трудно понять, что за чем идёт)
//{
//	if (thiis->Right) fastVivod1(thiis->Right, kolvoProbelov + 1, strochka + 1, maxDalni, fl);
//	else for (int i = 0; i < (maxDalni - strochka); i++) fprintf(fl, "\n");
//	for (int i = 0; i < kolvoProbelov; i++) fprintf(fl, "          ");
//	fprintf(fl, "%d [%d]\n", thiis->Vulue, thiis->Wight);
//	if (thiis->Left) fastVivod1(thiis->Left, kolvoProbelov + 1, strochka + 1, maxDalni, fl);
//	else for (int i = 0; i < (maxDalni - strochka); i++) fprintf(fl, "\n");
//}

void newVivod(struct Node* ths, long level, FILE* fl, long* mestoVstrochke, long strochka, long maxLevel)
{
	printf("%d - maxLevel", maxLevel);
	printf(", %d - level\n", level);
	if (level == 0) // Если он выше всех
	{
		for (long int i = 0; i <= maxLevel; i++) fprintf(fl, "     ");
		fprintf(fl, "[%d]", ths->Vulue);
	}
	else
	{
		long vr = BlijaishiNePustoi(ths, 0, 0, maxLevel, 1);
		if (mestoVstrochke[strochka])
		{
			fseek(fl, mestoVstrochke[strochka], SEEK_SET);
			//for (long int i = 0; i <= maxLevel; i++) fprintf(fl, "     ");
		}
		if (!mestoVstrochke[strochka])
		{
			//fprintf(fl, "                                                                                                                        \n");
		}
		vr;
		for (long int i = 0; i < vr; i++) fprintf(fl, "     ");
		fprintf(fl, "[%d]", ths->Vulue);
		for (int u = 0; u < (maxLevel - 1); u++)
		{
			fprintf(fl, "    ");
		}
		mestoVstrochke[strochka] = ftell(fl);
		//printf("(T_T)");
	}
	//nachalostroki = ftell(fl);
	if (ths->Left) newVivod(ths->Left, level + 1, fl, mestoVstrochke, strochka + 1, maxLevel - 1);
	if (ths->Right) newVivod(ths->Right, level + 1, fl, mestoVstrochke, strochka + 1, maxLevel - 1);
}

void vivod(struct Node* thiis, long riad, long simbol, FILE* fl) // Выводит знаяение и координаты (визуално трудно понять, что за чем идёт)
{
	fprintf(fl, "%d (%d, %d)[%d];	", thiis->Vulue, riad, simbol, thiis->Wight);
	if (thiis->Left) vivod(thiis->Left, riad + 1, simbol * 2 - 1, fl);
	if (thiis->Right) vivod(thiis->Right, riad + 1, simbol * 2, fl);
}


int mainnn()
{
	int ch = 8;
	ch--;
	ch--;

	//	//int w = 32;
	//	int maxLevel = 0, vr = 1;
	//	//while (w > 0)
	//	//{
	//	//	w -= vr;
	//	//	maxLevel++;
	//	//	vr *= 2;
	//	//}
	//	//for (int i = 1; i <= w; i++) 
	//	maxLevel = -maxLevel;
	//	printf("%d - max level", maxLevel);
}


int main()
{
	char* a;
	long* dliaVida, dliaVida2;
	struct Node* TOP = NULL;
	struct Node* b = NULL;
	long dlina = 0, i = 0, nachalostroki = 0, stroka = 0, cheslo = 0;
	char c;
	FILE* f0 = fopen("Text5.txt", "r");
	FILE* f_1 = fopen("Text-1.txt", "w");
	fseek(f0, 0, SEEK_END);
	long size = ftell(f0);
	fseek(f0, 0, SEEK_SET);
	while (ftell(f0) < size)
	{
		nachalostroki = ftell(f0);
		c = fgetc(f0);
		while ((c != '\n') && (c != EOF))
		{
			dlina++;
			c = fgetc(f0);
		}
		fseek(f0, nachalostroki, SEEK_SET);
		a = (char*)calloc(dlina + 1, sizeof(char));
		c = fgetc(f0);
		while ((c != '\n') && (c != EOF))
		{
			c = (c - '0');
			a[i] = c;
			i++;
			c = fgetc(f0);
		}
		b = (struct Node*)calloc(1, sizeof(struct Node));
		for (int u = 0; u < dlina; u++)
		{
			if (cheslo > 214748363)
			{
				printf("Error: too large number is set");
				exit(01);
			}
			cheslo = cheslo * 10 + a[u];
		}
		if (!TOP)
		{
			TOP = b;
			TOP->Vulue = cheslo;
		}
		else dobavka(TOP, cheslo, b);
		//printf("%d - chislo\n", cheslo);
		proverkaMasiva(TOP);
		TOP = poiskVershins(TOP);
		raschotVesa(TOP);
		polnaiaOptomizacia(TOP, samiGluboki(TOP, 1) - 3);
		TOP = poiskVershins(TOP);
		raschotVesa(TOP);
		//printf("\n");
		//fastVivod2(TOP, 0, 0, samiGluboki(TOP, 0), stdout);
		//printf("\n");
		//printf("\n");
		//printf("\n");
		dlina = 0;
		free(a);
		i = 0;
		stroka++;
		cheslo = 0;
	}
	fclose(f0);
	printf("\n");
	if (TOP)
	{
		TOP = poiskVershins(TOP);
		raschotVesa(TOP);
		//vivod(TOP, 1, 1, f_1);
		//fprintf(f_1, "\n");
		fastVivod2(TOP, 0, 0, samiGluboki(TOP, 0), stdout);
		fastVivod2(TOP, 0, 0, samiGluboki(TOP, 0), f_1);
		//printf("%d - maxLevel", (long)pow(2, samiGluboki(TOP, 0)) / 2);
		//dliaVida = (long*)calloc(samiGluboki(TOP, 0) + 1, sizeof(long));
		//fprintf(f_1, "\n");
		//newVivod(TOP, 0, f_1, dliaVida, 0, (long)pow(2, samiGluboki(TOP, 0)) / 2);
		//printf("\n");
		//dliaVida2 = (long*)calloc(samiGluboki(TOP, 0) + 1, sizeof(long));
		//newVivod(TOP, 0, stdout, dliaVida2, 0, pow(2, samiGluboki(TOP, 0)) / 2);

	}
	else
	{
		printf("Error: TOP is LOST");
		exit(02);
	}
	if (samiGluboki(TOP, 1) == schetMaxUrovnia(TOP->Wight + 1)) printf("\nAll is good! Well done!");
	else printf("\nIt doesn't work properly.(T_T)");
	//getchar();
	//printf("I didn't find the head (T_T)");
}