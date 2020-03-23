#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

#define duracao 3             // duracao em segundos
#define fc 1000               // frequencia de corte em hertz
#define fh 500                // frequencia de corte em hertz
#define fl 1500               // frequencia de corte em hertz
#define fa 20000              // frequencia de amostragem em hertz
#define wc 2 * M_PI * fc / fa // freq de corte angular normalizada
#define wh 2 * M_PI * fh / fa // freq de corte angular normalizada
#define wl 2 * M_PI * fl / fa // freq de corte angular normalizada
#define M 200                 // ordem do filtro

using namespace std;

float resposta_pb(int n) {
    if (n == M/2) {
        return wc/M_PI;
    }
    int shift_n = n - M/2;
    return sin(wc * shift_n)/(M_PI * shift_n);
}

float resposta_pa(int n) {
    if (n == M/2) {
        return 1 - wc/M_PI;
    }
    int shift_n = n - M/2;
    return -sin(wc * shift_n)/(M_PI * shift_n);
}

float resposta_pf(int n) {
    if (n == M/2) {
        return (wh - wl)/M_PI;
    }
    int shift_n = n - M/2;
    float sin_h = sin(wh * shift_n)/(M_PI * shift_n);
    float sin_l = sin(wl * shift_n)/(M_PI * shift_n);

    return sin_h - sin_l;
}

float hamming(int n) {
    return 0.54 - 0.46 * cos(2 * M_PI * n / M);
}

int main(int argc, char **argv)
{
    // cout << "GRAVANDO" << endl;
    // system(("python3 scripts/record.py " + to_string(fa) + " " + to_string(duracao)).c_str());
    // cout << "FIM  DA GRAVACAO" << endl;

    ifstream* input = new ifstream;
    ofstream* output = new ofstream;
    ofstream* resposta = new ofstream;
    ofstream* janela = new ofstream;
    ofstream* coeficiente = new ofstream;

    input->open("dados/input");
    if (!input->is_open()){
        cout << "Arquivo de entrada nao existe" << endl;
        return -1;
    }

    output->open("dados/output");
    if (!output->is_open()){
        cout << "Arquivo de saida nao existe" << endl;
        return -1;
    }

    resposta->open("dados/resposta");
    if (!resposta->is_open()){
        cout << "Arquivo de resposta nao existe" << endl;
        return -1;
    }

    janela->open("dados/janela");
    if (!janela->is_open()){
        cout << "Arquivo de resposta nao existe" << endl;
        return -1;
    }

    coeficiente->open("dados/coeficiente");
    if (!coeficiente->is_open()){
        cout << "Arquivo de coeficiente nao existe" << endl;
        return -1;
    }

    int qtd_amostras = duracao * fa;
    float amostras[qtd_amostras];
    for (int i = 0; i < qtd_amostras; i++) {
        *input >> amostras[i];
    }

    float h[M + 1];
    for (int i = 0; i < (M + 1); i++) {
        *resposta << resposta_pf(i) << endl;
        *janela << hamming(i) << endl;
        h[i] = resposta_pf(i) * hamming(i);
        *coeficiente << h[i] << endl;
    }


    float conv = 0;
    for (int i = 0; i < qtd_amostras; i++) {
        conv = 0;
        for (int j = 0; j < (M + 1) && j <= i; j++) {
            conv += amostras[i-j]*h[j];
        }
        *output << conv << endl;
    }

    input->close();
    output->close();
    system(("python3 scripts/process.py " + to_string(fa)).c_str()); // Converte txt para wav
    system(("python3 scripts/plot_fir.py " + to_string(fa)).c_str()); // mostra os dados
    // system("mpv dados/output.wav");
    return 0;
}
