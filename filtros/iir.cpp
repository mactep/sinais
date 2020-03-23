#include <fstream>
#include <iostream>
#include <math.h>

#define duracao 3             // duracao em segundos
#define fc 1000                // frequencia de corte em hertz
#define fa 20000              // frequencia de amostragem em hertz
#define wc 2 * M_PI * fc / fa // freq de corte angular normalizada
#define M 5                   // ordem do filtro

using namespace std;

int main(int argc, char **argv)
{
    // cout << "GRAVANDO" << endl;
    // system(("python3 scripts/record.py " + to_string(fa) + " " + to_string(duracao)).c_str());
    // cout << "FIM  DA GRAVACAO" << endl;

    system(("python3 scripts/butterworth.py " + to_string(M) + " " + to_string(fa) + " " + to_string(fc)).c_str());

    ifstream *input = new ifstream;
    ifstream *coeficiente = new ifstream;
    ofstream *output = new ofstream;
    ofstream *resposta = new ofstream;

    input->open("dados/input");
    if (!input->is_open())
    {
        cout << "Arquivo de entrada nao existe" << endl;
        return -1;
    }

    output->open("dados/output");
    if (!output->is_open())
    {
        cout << "Arquivo de saida nao existe" << endl;
        return -1;
    }

    resposta->open("dados/resposta");
    if (!resposta->is_open())
    {
        cout << "Arquivo de resposta nao existe" << endl;
        return -1;
    }

    coeficiente->open("dados/coeficientes_iir");
    if (!coeficiente->is_open())
    {
        cout << "Arquivo de coeficiente nao existe" << endl;
        return -1;
    }

    // int M;
    // *coeficiente >> M;
    // int fa;
    // *coeficiente >> fa;
    double b[M+1];
    double a[M+1];
    for (int i = 0; i < (M + 1); i++)
    {
        *coeficiente >> b[i];
    }
    for (int i = 0; i < (M + 1); i++)
    {
        *coeficiente >> a[i];
    }

    int qtd_amostras = duracao * fa;
    double amostras[qtd_amostras];
    double impulso[qtd_amostras];
    for (int i = 0; i < qtd_amostras; i++)
    {
        *input >> amostras[i];

        if (i == 0) {
            impulso[i] = 1;
        } else {
            impulso[i] = 0;
        }
    }

    double saida[duracao * fa];
    double resp_inpulso[duracao * fa];
    for (int i = 0; i < qtd_amostras; i++)
    {
        saida[i] = 0;
        resp_inpulso[i] = 0;

        for (int j = 0; j < (M + 1) && j <= i; j++)
        {
            saida[i] += a[j]*amostras[i-j];
            resp_inpulso[i] += a[j]*impulso[i-j];
            //saida += amostras[i - j] * h[j];
        }
        for (int j = 1; j < (M + 1) && j <= i; j++)
        {
            saida[i] -= b[j]*saida[i-j];
            resp_inpulso[i] -= b[j]*resp_inpulso[i-j];
        }
        saida[i] /= b[0];
        resp_inpulso[i] /= b[0];

        *output << saida[i] << endl;
        *resposta << resp_inpulso[i] << endl;
    }

    input->close();
    output->close();
    system(("python3 scripts/process.py " + to_string(fa)).c_str()); // Converte txt para wav
    system(("python3 scripts/plot_iir.py " + to_string(fa) + " " + to_string(duracao)).c_str());
    return 0;
}
