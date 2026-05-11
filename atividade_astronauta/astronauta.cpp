#include <iostream>
#include <string>
#include <vector>
using namespace std;


// Enum para representar o estado do voo
enum EstadoVoo {
    PLANEJADO,
    EM_CURSO,
    FINALIZADO_SUCESSO,
    FINALIZADO_EXPLOSAO
};

// Criação da classe Astronauta
class Astronauta {
    private:
        string cpf;
        int idade;
        string nome;
        bool vivo;
        bool disponivel;

    public:
    //Construtor da classe Astronauta
    Astronauta(string cpf_param, int idade_param, string nome_param) {
        cout << "Cadastrando astronauta: " << cpf_param << endl;
        this->cpf = cpf_param;
        this->idade = idade_param;
        this->nome = nome_param;
        this->vivo = true; 
        this->disponivel = true; 

    }

    string getCpf() {
        return this->cpf;
    }

    int getIdade() {
        return this->idade;
    }

    string getNome() {
        return this->nome;
    }

    bool isVivo() {
        return this->vivo;
    }

    bool isDisponivel() {
        return this->disponivel;
    }

    void setDisponivel(bool disponivel) {
        this->disponivel = disponivel;
    }

    void setVivo(bool vivo) {
        this->vivo = vivo;
    }

    //Destrutor da classe Astronauta
    ~Astronauta() {
        cout << "Excluindo astronauta: " << this->cpf << endl;
    }

};

// Criação da classe Voo
class Voo {
    private:
        int codigoVoo;
        vector<Astronauta*> astronautas;
        EstadoVoo estadoVoo;


    public:
    //Construtor da classe Voo
    Voo(int codigo_param) {
        cout << "Criando voo: " << codigo_param << endl;
        this->codigoVoo = codigo_param;
        this->estadoVoo = EstadoVoo::PLANEJADO; 
    }

    int getCodigoVoo() {
        return this->codigoVoo;
    }

    EstadoVoo getEstadoVoo() {
        return this->estadoVoo;
    }

    void setEstadoVoo(EstadoVoo estado) {
        this->estadoVoo = estado;
    }

    void adicionarAstronauta(Astronauta* astronauta) {
        this->astronautas.push_back(astronauta);
    }

    const vector<Astronauta*>& getAstronautas() const {
        return this->astronautas;
    }
    
    bool removerAstronauta(string cpf) {
        for (auto it = astronautas.begin(); it != astronautas.end(); ++it) {
            if ((*it)->getCpf() == cpf) {
                astronautas.erase(it); 
                return true; 
            }
        }
        return false;
    }


    //Destrutor da classe Voo
    ~Voo() {
        cout << "Excluindo voo: " << this->codigoVoo << endl;
    }
};

// Função auxiliar para buscar um astronauta pelo CPF
Astronauta* buscarAstronauta(vector<Astronauta*>& todosAstronautas, string cpf) {
    for (Astronauta* astronauta : todosAstronautas) {
        if (astronauta->getCpf() == cpf) {
            return astronauta;
        }
    }
    return nullptr;
}

// Função auxiliar para buscar um voo pelo código
Voo* buscarVoo(vector<Voo*>& todosVoos, int codigoVoo){
    for (Voo* voo : todosVoos) {
        if (voo->getCodigoVoo() == codigoVoo){
            return voo;
        }
    }
    return nullptr;
}

// Função para cadastrar um novo astronauta
void cadastrarAstronauta(vector<Astronauta*>& todosAstronautas, string cpf, int idade, string nome) {

    if (buscarAstronauta(todosAstronautas, cpf)) {
        cout << "CPF já existente: " << cpf << "Erro: Não foi possível criar o astronauta" << endl;
    } else {
        Astronauta* novoAstronauta = new Astronauta(cpf, idade, nome);
        todosAstronautas.push_back(novoAstronauta);
    }
}

// Função para cadastrar um novo voo
void cadastrarVoo(vector<Voo*>& todosVoos, int codigoVoo) {
    if (buscarVoo(todosVoos, codigoVoo)) {
        cout << "Código de voo já existente: " << codigoVoo << "Erro: Não foi possível criar o voo" << endl;
    } else {
        Voo* novoVoo = new Voo(codigoVoo);
        todosVoos.push_back(novoVoo);
    }
}

// Função para adicionar um astronauta a um voo
void adicionarAstronauta(vector<Astronauta*>& todosAstronautas, vector<Voo*>& todosVoos, string cpf, int codigoVoo) {
    Astronauta* astronauta = buscarAstronauta(todosAstronautas, cpf);
    Voo* voo = buscarVoo(todosVoos, codigoVoo);

    if(astronauta == nullptr || voo == nullptr) {
        cout << "Erro: Astronauta ou voo não encontrado" << endl;
        return;
    }

    if(voo->getEstadoVoo() != EstadoVoo::PLANEJADO) {
        cout << "Erro: Voo não está em estado planejado" << endl;
        return;
    }

    if(!astronauta->isDisponivel()) {
        cout << "Erro: Astronauta não está disponível" << endl;
        return;
    }

    if(!astronauta->isVivo()) {
        cout << "Erro: Astronauta não está vivo" << endl;
        return;
    }

    for (Astronauta* astro : voo->getAstronautas()) {
        if (astro->getCpf() == cpf) {
            cout << "Erro: Astronauta já está no voo" << endl;
            return;
        }
    }

    voo->adicionarAstronauta(astronauta);
}

// Função para remover um astronauta de um voo
void removerAstronauta(vector<Astronauta*>& todosAstronautas, vector<Voo*>& todosVoos, string cpf, int codigoVoo) {
    Astronauta* astronauta = buscarAstronauta(todosAstronautas, cpf);
    Voo* voo = buscarVoo(todosVoos, codigoVoo);

    if(astronauta == nullptr || voo == nullptr) {
        cout << "Erro: Astronauta ou voo não encontrado" << endl;
        return;
    }

    if(voo->getEstadoVoo() != EstadoVoo::PLANEJADO) {
        cout << "Erro: Voo não está em estado planejado" << endl;
        return;
    }

    bool removido = voo->removerAstronauta(cpf);
    if (!removido) {
        cout << "Erro: Astronauta não está no voo" << endl;
    }

    cout << "Astronauta removido do voo com sucesso" << endl;

}

// Função para lançar um voo
void lancarVoo(vector<Voo*>& todosVoos, int codigoVoo) {
    Voo* voo = buscarVoo(todosVoos, codigoVoo);

    if (voo == nullptr) {
        cout << "Erro: Voo não encontrado" << endl;
        return;
    }

    if (voo->getEstadoVoo() != EstadoVoo::PLANEJADO) {
        cout << "Erro: Voo não está em estado planejado" << endl;
        return;
    }

    if (voo->getAstronautas().empty()) {
        cout << "Erro: Voo não tem astronautas" << endl;
        return;
    }

    for (Astronauta* astro : voo->getAstronautas()) {
        if (!astro->isVivo() || !astro->isDisponivel()) {
            cout << "Erro: O astronauta CPF " << astro->getCpf() << " não está vivo ou disponível para o lançamento." << endl;
            return;
        }
    }

    voo->setEstadoVoo(EstadoVoo::EM_CURSO);

    for (Astronauta* astro : voo->getAstronautas()) {
        astro->setDisponivel(false);
    }

    cout << "Sucesso: Voo " << codigoVoo << " lançado com sucesso!" << endl;
}

// Função para explodir um voo
void explodirVoo(vector<Voo*>& todosVoos, int codigoVoo) {
    Voo* voo = buscarVoo(todosVoos, codigoVoo);

    if (voo == nullptr) {
        cout << "Erro: Voo não encontrado" << endl;
        return;
    }

    if (voo->getEstadoVoo() != EstadoVoo::EM_CURSO) {
        cout << "Erro: Voo não está em curso" << endl;
        return;
    }

    voo->setEstadoVoo(EstadoVoo::FINALIZADO_EXPLOSAO);

    for (Astronauta* astro : voo->getAstronautas()) {
        astro->setVivo(false);
        astro->setDisponivel(false);
    }

    cout << "Voo explodido com sucesso!" << endl;

}

// Função para finalizar um voo com sucesso
void finalizarVoo(vector<Voo*>& todosVoos, int codigoVoo) {
    Voo* voo = buscarVoo(todosVoos, codigoVoo);

    if (voo == nullptr) {
        cout << "Erro: Voo não encontrado" << endl;
        return;
    }

    if (voo->getEstadoVoo() != EstadoVoo::EM_CURSO) {
        cout << "Erro: Voo não está em curso" << endl;
        return;
    }

    voo->setEstadoVoo(EstadoVoo::FINALIZADO_SUCESSO);

    for (Astronauta* astro : voo->getAstronautas()) {
        astro->setDisponivel(true);
    }

    cout << "Voo finalizado com sucesso!" << endl;
}

// Função para listar todos os voos e seus astronautas
void listarVoos(vector<Voo*>& todosVoos) {
    if (todosVoos.empty()) {
        cout << "Nenhum voo cadastrado." << endl;
        return;
    }

    for (Voo* voo : todosVoos) {
        cout << "Código do Voo: " << voo->getCodigoVoo() << endl;
        cout << "Estado do Voo: ";
        switch (voo->getEstadoVoo()) {
            case PLANEJADO:
                cout << "Planejado";
                break;
            case EM_CURSO:
                cout << "Em Curso";
                break;
            case FINALIZADO_SUCESSO:
                cout << "Finalizado com Sucesso";
                break;
            case FINALIZADO_EXPLOSAO:
                cout << "Finalizado por Explosão";
                break;
        }
        cout << endl;

        if (voo->getAstronautas().empty()) {
            cout << "Nenhum astronauta neste voo." << endl;
        } else {
            cout << "Astronautas no Voo:" << endl;
            for (Astronauta* astro : voo->getAstronautas()) {
                cout << "- CPF: " << astro->getCpf() 
                     << ", Nome: " << astro->getNome() 
                     << ", Idade: " << astro->getIdade() 
                     << ", Vivo: " << (astro->isVivo() ? "Sim" : "Não") 
                     << ", Disponível: " << (astro->isDisponivel() ? "Sim" : "Não") 
                     << endl;
            }
        }
        cout << endl; 
    }

    
}

// Função para listar os astronautas mortos
void listarMortos(vector<Astronauta*>& todosAstronautas) {
    bool encontrouMortos = false;
    for (Astronauta* astro : todosAstronautas) {
        if (!astro->isVivo()) {
            if (!encontrouMortos) {
                cout << "Astronautas mortos:" << endl;
                encontrouMortos = true;
            }
            cout << "- CPF: " << astro->getCpf() 
                 << ", Nome: " << astro->getNome() 
                 << ", Idade: " << astro->getIdade() 
                 << endl;
        }
    }
    if (!encontrouMortos) {
        cout << "Nenhum astronauta morto." << endl;
    }
}


int main() {
    vector<Astronauta*> todosAstronautas;
    vector<Voo*> todosVoos;

    string comando;

    while (cin >> comando) {

        // Condicionais para executar os comandos de acordo com a entrada do usuário
        // Comando para encerrar o programa
        if (comando == "FIM"){
            break;
        }

        // Comando para cadastrar um novo astronauta
        if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;

            cin >> cpf >> idade;
            getline(cin >> ws, nome);

            cadastrarAstronauta(todosAstronautas, cpf, idade, nome);
        }

        // Comando para criar um novo voo
        else if (comando == "CADASTRAR_VOO") {
            int codigoVoo;
            cin >> codigoVoo;

            cadastrarVoo(todosVoos, codigoVoo);
        }

        else if (comando == "ADICIONAR_ASTRONAUTA"){
                int codigoVoo;
                string cpf;
    
                cin >> cpf >> codigoVoo;

                adicionarAstronauta(todosAstronautas, todosVoos, cpf, codigoVoo);
        }

        else if (comando == "REMOVER_ASTRONAUTA"){
                int codigoVoo;
                string cpf;

                cin >> codigoVoo >> cpf;

                removerAstronauta(todosAstronautas, todosVoos, cpf, codigoVoo);
        }

        else if(comando == "LANCAR_VOO") {
            int codigoVoo;
            
            cin >> codigoVoo;

            lancarVoo(todosVoos, codigoVoo);
        }

        else if (comando == "EXPLODIR_VOO") {
            int codigoVoo;

            cin >> codigoVoo;

            explodirVoo(todosVoos, codigoVoo);

        }

        else if (comando == "FINALIZAR_VOO") {
            int codigoVoo;

            cin >> codigoVoo;

            finalizarVoo(todosVoos, codigoVoo);

        }

        else if (comando == "LISTAR_VOOS") {
            listarVoos(todosVoos);
        }

        else if (comando == "LISTAR_MORTOS") {
            listarMortos(todosAstronautas);
        }
    }

    for (Astronauta* astro : todosAstronautas) {
        delete astro;
    }

    for (Voo* voo : todosVoos) {
        delete voo;
    }

    return 0;
}


    

