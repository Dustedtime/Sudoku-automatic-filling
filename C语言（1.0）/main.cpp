#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	srand((unsigned)time(NULL));
	void check(int(*aa)[9][10]);
	int a[9][9][10] = { 0 }, n, m, y = 0, d, b, f = 1, g, h[9] = { 0 }, i, j, k, p = 1, q = 0, r = 1;
	char c;
    char shuzu[11] = "0123456789";
	printf("请按顺序输入每行数据，空格填零\n");
	for (n = 0; n < 9; n++)
	{
		printf("输入第%d行数据：", n + 1);
		for (m = 0; m < 9; m++)
			scanf_s("%1d", &a[n][m][0]);
		while (getchar() != '\n')
			continue;
	}
	int iii = 0;
	for (n = m = 0; n != 8 || m != 9; m++)
	{
		if (m >= 9)
		{
			m = 0;
			n++;
		}
		if (a[n][m][0])
			iii++;
	}
	if (!iii)
	{
		printf("检测到无数据输入，将随机为第一个数赋值：");
		a[0][0][0] = rand() % 9 + 1;
		printf("%d\n", a[0][0][0]);
	}
	printf("按下回车显示数独未填写时图像，再按一次显示填写完成的数独");
	c = getchar();
	initgraph(480, 480);
	setfillcolor(WHITE);
	bar(1, 1, 478, 478);
	setlinestyle(0, 3);
	setlinecolor(BLACK);
	for (m = 1; m <= 478; m += 53)
	{
		line(0, m, 479, m);
		line(m, 0, m, 479);
	}
	settextstyle(40, 0, 0);
	setfillcolor(RGB(211, 211, 211));
	setbkcolor(RGB(211, 211, 211));
	settextcolor(BLACK);
	for (n = m = 0; n != 8 || m != 9; m++)
	{
		if (m >= 9)
		{
			m = 0;
			n++;
		}
		floodfill(3 + m * 53, 3 + n * 53, BLACK);
		if (a[n][m][0])
			outtextxy(18 + m * 53, 8 + n * 53, shuzu[a[n][m][0]]);
	}
	c = getchar();
	for (m = n = 0; m != 9 || n != 8; m++)
	{
		if (m > 8)
		{
			m = 0;
			n++;
		}
		if (a[n][m][0])
		{
			for (b = 0; b < 9; b++)
				if (!a[n][b][0])
					a[n][b][a[n][m][0]] = a[n][m][0];
			for (b = 0; b < 9; b++)
				if (!a[b][m][0])
					a[b][m][a[n][m][0]] = a[n][m][0];
			for (b = int(n / 3) * 3, d = int(m / 3) * 3; b != int(n / 3) * 3 + 2 || d != int(m / 3) * 3 + 3; d++)
			{
				if (d > int(m / 3) * 3 + 2)
				{
					d = int(m / 3) * 3;
					b++;
				}
				if (!a[b][d][0])
					a[b][d][a[n][m][0]] = a[n][m][0];
			}
		}
	}
	for (;;)
	{
		for (n = m = 0; n != 8 || m != 9; m++)
		{
			if (m >= 9)
			{
				m = 0;
				n++;
			}
			if (!a[n][m][0])
				break;
			if (m == 8 && n == 8)
			{
				y = 1;
				break;
			}
		}
		if (y == 1)
			break;
		if (!f) 
		{
			for (m = n = 0, p = 0; m != 9 || n != 6; m += 3)
			{
				if (m > 8)
				{
					m = 0;
					n += 3;
				}
				for (f = 1; f < 10; f++)
				{
					for (b = d = i = 0; b != 2 || d != 3; d++)
					{
						if (d > 2)
						{
							d = 0;
							b++;
						}
						if (!a[n + b][m + d][0] && !a[n + b][m + d][f])
						{
							h[i] = 3 * b + d + 1;
							i++;
						}
					}
					if (i == 1)
					{
						j = (h[0] - 1) / 3;
						k = h[0] - 1 - j * 3;
						a[n + j][m + k][0] = f;
						for (b = 0; b < 9; b++)
							if (!a[n + j][b][0])
								a[n + j][b][f] = f;
						for (b = 0; b < 9; b++)
							if (!a[b][m + k][0])
								a[b][m + k][f] = f;
						p++;
					}
					else if (i == 2)
					{
						if (h[0] == h[1] - 3)
						{
							j = (h[0] - 1) / 3;
							k = h[0] - 1 - j * 3;
							for (b = 0; b < 9; b++)
								if (!a[b][m + k][0] && b < n + j && b > n + j + 1)
								{
									if (!a[b][m + k][f])
										q++;
									a[b][m + k][f] = f;
								}
							if (q)
							{
								q = 0;
								p++;
							}
						}
						else if ((h[0] - 1) / 3 == (h[1] - 1) / 3)
						{
							j = (h[0] - 1) / 3;
							k = h[0] - 1 - j * 3;
							for (b = 0; b < 9; b++)
								if (!a[n + j][b][0] && b < m + k && b > m + k + 1)
								{
									if (!a[n + j][b][f])
										q++;
									a[n + j][b][f] = f;
								}
							if (q)
							{
								q = 0;
								p++;
							}
						}
					}
					else if (i == 3)
					{
						if (h[0] == h[1] - 3 && h[1] == h[2] - 3)
						{
							j = (h[0] - 1) / 3;
							k = h[0] - 1 - j * 3;
							for (b = 0; b < 9; b++)
								if (!a[b][m + k][0] && b < n + j && b > n + j + 2)
								{
									if (!a[b][m + k][f])
										q++;
									a[b][m + k][f] = f;
								}
							if (q)
							{
								q = 0;
								p++;
							}
						}
						else if ((h[0] - 1) / 3 == (h[1] - 1) / 3 && (h[1] - 1) / 3 == (h[2] - 1) / 3)
						{
							j = (h[0] - 1) / 3;
							k = h[0] - 1 - j * 3;
							for (b = 0; b < 9; b++)
								if (!a[n + j][b][0] && b < m + k && b > m + k + 2)
								{
									if (!a[n + j][b][f])
										q++;
									a[n + j][b][f] = f;
								}
							if (q)
							{
								q = 0;
								p++;
							}
						}
					}
					for (i = 0; i < 9; i++)
						h[i] = 0;
				}
			}
		}
		if (!p)
			check(a);
		for (m = n = 0, f = 0; m != 9 || n != 8; m++)
		{
			if (m > 8)
			{
				m = 0;
				n++;
			}
			if (!a[n][m][0])
			{
				for (d = 0, b = 1, g = 0; b < 10; b++)
				{
					g += a[n][m][b];
					if (!a[n][m][b])
						d++;
				}
				if (d == 1)
				{
					f = 1;
					a[n][m][0] = 45 - g;
					for (b = 0; b < 9; b++)
						if (!a[n][b][0])
							a[n][b][a[n][m][0]] = a[n][m][0];
					for (b = 0; b < 9; b++)
						if (!a[b][m][0])
							a[b][m][a[n][m][0]] = a[n][m][0];
					for (b = int(n / 3) * 3, d = int(m / 3) * 3; b != int(n / 3) * 3 + 2 || d != int(m / 3) * 3 + 3; d++)
					{
						if (d > int(m / 3) * 3 + 2)
						{
							d = int(m / 3) * 3;
							b++;
						}
						if (!a[b][d][0])
							a[b][d][a[n][m][0]] = a[n][m][0];
					}
				}
			}
		}
		for (n = 0; n < 9; n++)
		{
			for (i = 1; i < 10; i++)
			{
				for (m = 0, j = 0; m < 9; m++)
				{
					if (!a[n][m][0] && !a[n][m][i])
					{
						k = m;
						j++;
					}
				}
				if (j == 1)
				{
					f = 1;
					a[n][k][0] = i;
					for (b = 0; b < 9; b++)
						if (!a[n][b][0])
							a[n][b][i] = i;
					for (b = 0; b < 9; b++)
						if (!a[b][k][0])
							a[b][k][i] = i;
					for (b = int(n / 3) * 3, d = int(k / 3) * 3; b != int(n / 3) * 3 + 2 || d != int(k / 3) * 3 + 3; d++)
					{
						if (d > int(k / 3) * 3 + 2)
						{
							d = int(k / 3) * 3;
							b++;
						}
						if (!a[b][d][0])
							a[b][d][i] = i;
					}
				}
			}
		}
		for (m = 0; m < 9; m++)
		{
			for (i = 1; i < 10; i++)
			{
				for (n = 0, j = 0; n < 9; n++)
				{
					if (!a[n][m][0] && !a[n][m][i])
					{
						k = n;
						j++;
					}
				}
				if (j == 1)
				{
					f = 1;
					a[k][m][0] = i;
					for (b = 0; b < 9; b++)
						if (!a[k][b][0])
							a[k][b][i] = i;
					for (b = 0; b < 9; b++)
						if (!a[b][m][0])
							a[b][m][i] = i;
					for (b = int(k / 3) * 3, d = int(m / 3) * 3; b != int(k / 3) * 3 + 2 || d != int(m / 3) * 3 + 3; d++)
					{
						if (d > int(m / 3) * 3 + 2)
						{
							d = int(m / 3) * 3;
							b++;
						}
						if (!a[b][d][0])
							a[b][d][i] = i;
					}
				}
			}
		}
	}
	for (n = m = 0; n != 8 || m != 9; m++)
	{
		if (m >= 9)
		{
			m = 0;
			n++;
		}
		if (a[n][m][0])
			outtextxy(18 + m * 53, 8 + n * 53, shuzu[a[n][m][0]]);
	}
	c = getchar();
	closegraph;
	return 0;
}

void check(int(*aa)[9][10])
{
	int a[9][9][10], m, n, b, c = 9, d, f = 1, g, i, j, k, p = 1, q = 0, s = 9, m1 = 0, n1 = 0, y = 0, r = 1;
	int t[9] = { 0 }, h[9] = { 0 };
	for (m = n = 0; m != 9 || n != 8; m++)
	{
		if (m > 8)
		{
			m = 0;
			n++;
		}
		for (b = 0; b < 10; b++)
			a[n][m][b] = aa[n][m][b];
	}
	for (m = n = 0; m != 9 || n != 8; m++)
	{
		if (m > 8)
		{
			m = 0;
			n++;
		}
		if(!a[n][m][0])
			for (b = 1, c = 0; b < 10; b++)
			{
				if (!a[n][m][b])
				{
					t[c] = b;
					c++;
				}
			}
		if (c < s)
		{
			s = c;
			n1 = n;
			m1 = m;
			for (b = 0; b < c; b++)
				h[b] = t[b];
		}
	}
	for (c = 0, m = m1, n = n1; c < s; c++)
	{
		for (m = n = 0; m != 9 || n != 8; m++)
		{
			if (m > 8)
			{
				m = 0;
				n++;
			}
			for (b = 0; b < 10; b++)
				a[n][m][b] = aa[n][m][b];
		}
		m = m1;
		n = n1;
		a[n][m][0] = h[c];
		for (b = 0; b < 9; b++)
			if (!a[n][b][0])
				a[n][b][a[n][m][0]] = a[n][m][0];
		for (b = 0; b < 9; b++)
			if (!a[b][m][0])
				a[b][m][a[n][m][0]] = a[n][m][0];
		for (b = int(n / 3) * 3, d = int(m / 3) * 3; b != int(n / 3) * 3 + 2 || d != int(m / 3) * 3 + 3; d++)
		{
			if (d > int(m / 3) * 3 + 2)
			{
				d = int(m / 3) * 3;
				b++;
			}
			if (!a[b][d][0])
				a[b][d][a[n][m][0]] = a[n][m][0];
		}
		for (;;)
		{
			for (n = m = 0; n != 8 || m != 9; m++)
			{
				if (m >= 9)
				{
					m = 0;
					n++;
				}
				if (!a[n][m][0])
					break;
				if (m == 8 && n == 8)
				{
					y = 1;
					break;
				}
			}
			if (y == 1)
			{
				for (m = n = 0; m != 9 || n != 8; m++)
				{
					if (m > 8)
					{
						m = 0;
						n++;
					}
					aa[n][m][0] = a[n][m][0];
				}
				return;
			}
			if (!f)
			{
				for (m = n = 0, p = 0; m != 9 || n != 6; m += 3)
				{
					if (m > 8)
					{
						m = 0;
						n += 3;
					}
					for (f = 1; f < 10; f++)
					{
						for (b = d = i = 0; b != 2 || d != 3; d++)
						{
							if (d > 2)
							{
								d = 0;
								b++;
							}
							if (!a[n + b][m + d][0] && !a[n + b][m + d][f])
							{
								h[i] = 3 * b + d + 1;
								i++;
							}
						}
						if (i == 1)
						{
							j = (h[0] - 1) / 3;
							k = h[0] - 1 - j * 3;
							a[n + j][m + k][0] = f;
							for (b = 0; b < 9; b++)
								if (!a[n + j][b][0])
									a[n + j][b][f] = f;
							for (b = 0; b < 9; b++)
								if (!a[b][m + k][0])
									a[b][m + k][f] = f;
							p++;
						}
						else if (i == 2)
						{
							if (h[0] == h[1] - 3)
							{
								j = (h[0] - 1) / 3;
								k = h[0] - 1 - j * 3;
								for (b = 0; b < 9; b++)
									if (!a[b][m + k][0] && b < n + j && b > n + j + 1)
									{
										if (!a[b][m + k][f])
											q++;
										a[b][m + k][f] = f;
									}
								if (q)
								{
									q = 0;
									p++;
								}
							}
							else if ((h[0] - 1) / 3 == (h[1] - 1) / 3)
							{
								j = (h[0] - 1) / 3;
								k = h[0] - 1 - j * 3;
								for (b = 0; b < 9; b++)
									if (!a[n + j][b][0] && b < m + k && b > m + k + 1)
									{
										if (!a[n + j][b][f])
											q++;
										a[n + j][b][f] = f;
									}
								if (q)
								{
									q = 0;
									p++;
								}
							}
						}
						else if (i == 3)
						{
							if (h[0] == h[1] - 3 && h[1] == h[2] - 3)
							{
								j = (h[0] - 1) / 3;
								k = h[0] - 1 - j * 3;
								for (b = 0; b < 9; b++)
									if (!a[b][m + k][0] && b < n + j && b > n + j + 2)
									{
										if (!a[b][m + k][f])
											q++;
										a[b][m + k][f] = f;
									}
								if (q)
								{
									q = 0;
									p++;
								}
							}
							else if ((h[0] - 1) / 3 == (h[1] - 1) / 3 && (h[1] - 1) / 3 == (h[2] - 1) / 3)
							{
								j = (h[0] - 1) / 3;
								k = h[0] - 1 - j * 3;
								for (b = 0; b < 9; b++)
									if (!a[n + j][b][0] && b < m + k && b > m + k + 2)
									{
										if (!a[n + j][b][f])
											q++;
										a[n + j][b][f] = f;
									}
								if (q)
								{
									q = 0;
									p++;
								}
							}
						}
						for (i = 0; i < 9; i++)
							h[i] = 0;
					}
				}
			}
			if (!p)
				check(a);
			for (m = n = 0, f = 0; m != 9 || n != 8; m++)
			{
				if (m > 8)
				{
					m = 0;
					n++;
				}
				if (!a[n][m][0])
				{
					for (d = 0, b = 1, g = 0; b < 10; b++)
					{
						g += a[n][m][b];
						if (!a[n][m][b])
							d++;
					}
					if (d == 1)
					{
						f = 1;
						a[n][m][0] = 45 - g;
						for (b = 0; b < 9; b++)
							if (!a[n][b][0])
								a[n][b][a[n][m][0]] = a[n][m][0];
						for (b = 0; b < 9; b++)
							if (!a[b][m][0])
								a[b][m][a[n][m][0]] = a[n][m][0];
						for (b = int(n / 3) * 3, d = int(m / 3) * 3; b != int(n / 3) * 3 + 2 || d != int(m / 3) * 3 + 3; d++)
						{
							if (d > int(m / 3) * 3 + 2)
							{
								d = int(m / 3) * 3;
								b++;
							}
							if (!a[b][d][0])
								a[b][d][a[n][m][0]] = a[n][m][0];
						}
					}
					else if (!d)
						break;
				}
			}
			if (!d)
				break;
			for (n = 0; n < 9; n++)
			{
				for (i = 1; i < 10; i++)
				{
					for (m = 0, j = 0; m < 9; m++)
					{
						if (!a[n][m][0] && !a[n][m][i])
						{
							k = m;
							j++;
						}
					}
					if (j == 1)
					{
						f = 1;
						a[n][k][0] = i;
						for (b = 0; b < 9; b++)
							if (!a[n][b][0])
								a[n][b][i] = i;
						for (b = 0; b < 9; b++)
							if (!a[b][k][0])
								a[b][k][i] = i;
						for (b = int(n / 3) * 3, d = int(k / 3) * 3; b != int(n / 3) * 3 + 2 || d != int(k / 3) * 3 + 3; d++)
						{
							if (d > int(k / 3) * 3 + 2)
							{
								d = int(k / 3) * 3;
								b++;
							}
							if (!a[b][d][0])
								a[b][d][i] = i;
						}
					}
				}
			}
			for (m = 0; m < 9; m++)
			{
				for (i = 1; i < 10; i++)
				{
					for (n = 0, j = 0; n < 9; n++)
					{
						if (!a[n][m][0] && !a[n][m][i])
						{
							k = n;
							j++;
						}
					}
					if (j == 1)
					{
						f = 1;
						a[k][m][0] = i;
						for (b = 0; b < 9; b++)
							if (!a[k][b][0])
								a[k][b][i] = i;
						for (b = 0; b < 9; b++)
							if (!a[b][m][0])
								a[b][m][i] = i;
						for (b = int(k / 3) * 3, d = int(m / 3) * 3; b != int(k / 3) * 3 + 2 || d != int(m / 3) * 3 + 3; d++)
						{
							if (d > int(m / 3) * 3 + 2)
							{
								d = int(m / 3) * 3;
								b++;
							}
							if (!a[b][d][0])
								a[b][d][i] = i;
						}
					}
				}
			}
		}
		if (!d && c == s - 1)
		{
			for (m = n = 0; m != 9 || n != 8; m++)
			{
				if (m > 8)
				{
					m = 0;
					n++;
				}
				aa[n][m][0] = a[n][m][0];
			}
			return;
		}
	}
}
