#include "../include/Robo.hpp"

Robo::Robo()
{
    this->numRobo = 0;
    this->linhaX = -1;
    this->colunaY = -1;
    this->ativo = false;
    this->relatorio = "";
    this->totalRecursos = 0;
    this->totalAliens = 0;
    this->OrdensDeComando = new FilaEncadeada();
}

void Robo::SetRobo(int numRobo, int linhaX, int colunaY, bool ativo, std::string relatorio, int totalRecursos, int totalAliens, FilaEncadeada *OrdensDeComando)
{
    this->numRobo = numRobo;
    this->linhaX = linhaX;
    this->colunaY = colunaY;
    this->ativo = ativo;
    this->relatorio = relatorio;
    this->totalRecursos = totalRecursos;
    this->totalAliens = totalAliens;
    this->OrdensDeComando = OrdensDeComando;
}

void Robo::SetNumRobo(int numRobo)
{
    this->numRobo = numRobo;
}

void Robo::SetCoordenadas(int linhaX, int colunaY)
{
    this->linhaX = linhaX;
    this->colunaY = colunaY;
}

int Robo::GetNumRobo()
{
    return this->numRobo;
}

void Robo::ImprimeRobo()
{
    std::cout << "Num: " << this->numRobo << std::endl;
    std::cout << "LinhaX: " << this->linhaX << std::endl;
    std::cout << "ColunaY: " << this->colunaY << std::endl;
    std::cout << "Ativo: " << this->ativo << std::endl;
    std::cout << "TotalRecursos: " << this->totalRecursos << std::endl;
    std::cout << "TotalAliens: " << this->totalAliens << std::endl;
}

void Robo::SetAtivo()
{
    this->ativo = !this->ativo;
}

void Robo::SetRecursos()
{
    this->totalRecursos++;
}

void Robo::SetAliens()
{
    this->totalAliens++;
}

void Robo::SetRelatorio(std::string relatorio)
{
    this->relatorio = this->relatorio + relatorio + ";";
}

void Robo::SetOrdensDeComando(FilaEncadeada *ordensDeComando) { this->OrdensDeComando = ordensDeComando; }

FilaEncadeada *Robo::GetOrdensDeComando() { return this->OrdensDeComando; }

void Robo::ImprimeRelatorio()
{
    std::string delimiter = ";";
    std::string aux = this->relatorio;
    size_t pos = 0;
    std::string token;
    std::ofstream file("saida.txt", std::ofstream::app);
    while ((pos = aux.find(delimiter)) != std::string::npos)
    {
        token = aux.substr(0, pos);
        std::cout << token << std::endl;
        std::string num = std::to_string(GetNumRobo());
        file << "ROBO " << num << ": " << token <<"\n";
        aux.erase(0, pos + delimiter.length());
    }
    file.close();
}