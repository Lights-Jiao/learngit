#ifndef _KNAPSTACK_H__
#define _KNAPSTACK_H__

/* ������ϸ����˵�� */
/* http://www.hawstein.com/posts/dp-knapsack.html */

using namespace std;

#define KNAPSTACK_MANN 1000   //n ����ʯ
#define KNAPSTACK_MAXC 100000 //C ������

int knapstack_V[KNAPSTACK_MANN]; //volume(��ʯ���) 
int knapstack_W[KNAPSTACK_MANN]; //worth (��ʯ��ֵ)
int knapstack_X[KNAPSTACK_MANN]; //exist (��ʯ�Ƿ�װ��)

int knapstack_d[KNAPSTACK_MANN][KNAPSTACK_MAXC]; // d(i, j) = MAX{ d(i - 1, j), d(i-1,j - V[i-1]) + W[i-1] } �ı��ʽ

int test_knapstack()
{
    freopen("data.in", "r", stdin);   //�ض���������
    //freopen("data.out", "w", stdout); //�ض��������

    int n, C;

    while (scanf("%d %d", &n, &C) != EOF)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d %d", &knapstack_V[i], &knapstack_W[i]);
            knapstack_X[i] = 0;//��ʼ���Ƿ�װ����ӵĲ���
        }

        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= C; j++)
            {
                knapstack_d[i][j] = i == 0 ? 0 : knapstack_d[i - 1][j];
                if (i > 0 && j >= knapstack_V[i-1])
                {
                    if (knapstack_d[i][j] < knapstack_d[i - 1][j - knapstack_V[i - 1]] + knapstack_W[i - 1])
                    {
                        knapstack_d[i][j] = knapstack_d[i - 1][j - knapstack_V[i - 1]] + knapstack_W[i - 1];
                        
                        //knapstack_X[i-1] = 1; //�������Ĳ���Ϊʲô�����أ�
                    }
                    else
                    {
                        //knapstack_X[i-1] = 0;
                    }
                }
            }
        }
        printf("����ֵ��%d\n", knapstack_d[n][C]); //�����������ֵ
        
        //��ȷ��װ������
        int j = C;
        for (int i = n; i > 0; i--)
        {
            if (knapstack_d[i][j] > knapstack_d[i - 1][j])
            {
                knapstack_X[i - 1] = 1;
                j = j - knapstack_V[i - 1];
            }
        }

        printf("װ�����ԣ�");
        for (int i = 0; i < n ;i++)
        {
            printf("%d ", knapstack_X[i]);
        }
        printf("\n\n");
    }
    
    fclose(stdin);

    return 0;
}

#endif // _KNAPSTACK_H__
