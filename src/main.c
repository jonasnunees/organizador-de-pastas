#include <stdio.h>      // Permite usar funções de entrada e saída (como printf)
#include <stdlib.h>     // Permite usar funções padrão do C
#include <string.h>     // Permite manipular strings (texto)
#include <dirent.h>     // Permite acessar e ler o conteúdo de diretórios
#include <sys/stat.h>   // Permite criar pastas (diretórios)
#include <unistd.h>     // Permite manipular arquivos no sistema

// Ajuste para compatibilidade com Windows
#ifdef _WIN32
#include <windows.h>
#define PATH_SEP '\\'   // No Windows, o separador de pastas é a barra invertida
#else
#include <errno.h>
#define PATH_SEP '/'    // No Linux/Mac, o separador é a barra normal
#endif

// Função para criar uma subpasta dentro da pasta principal
void criar_pasta(const char *base, const char *nome) {
    char caminho[512];

    // Monta o caminho da nova pasta: exemplo -> /Downloads/Imagens
    snprintf(caminho, sizeof(caminho), "%s%c%s", base, PATH_SEP, nome);

    #ifdef _WIN32
        CreateDirectory(caminho, NULL);   // Cria pasta no Windows
    #else
        mkdir(caminho, 0755);             // Cria pasta no Linux/Mac
    #endif
}

// Função que move um arquivo de um local para outro
void mover_arquivo(const char *origem, const char *destino) {
    rename(origem, destino);  // Renomeia (ou move) o arquivo de um caminho para outro
}

// Função que classifica a extensão do arquivo em uma categoria (Imagens, Documentos, etc.)
const char* detectar_categoria(const char *extensao) {
    if (!extensao) return "Outros";  // Se não houver extensão, considera como "Outros"

    // Compara a extensão do arquivo e retorna o nome da categoria
    if (strcmp(extensao, ".jpg") == 0 || strcmp(extensao, ".png") == 0)
        return "Imagens";
    if (strcmp(extensao, ".pdf") == 0 || strcmp(extensao, ".docx") == 0)
        return "Documentos";
    if (strcmp(extensao, ".mp3") == 0)
        return "Músicas";

    return "Outros";  // Qualquer outra extensão vai pra "Outros"
}

// Função que pega a extensão do nome do arquivo (por exemplo: ".pdf")
const char* obter_extensao(const char *nome) {
    const char *ponto = strrchr(nome, '.');  // Encontra o último ponto no nome do arquivo
    return ponto ? ponto : NULL;             // Retorna a parte após o ponto, se existir
}

// Função principal que organiza os arquivos dentro da pasta
void organizar_pasta(const char *pasta) {
    DIR *dir = opendir(pasta);  // Abre a pasta indicada

    if (!dir) {
        perror("Erro ao abrir a pasta");  // Se não conseguir abrir, exibe o erro
        return;
    }

    struct dirent *entrada;

    // Lê cada item (arquivo ou pasta) dentro da pasta principal
    while ((entrada = readdir(dir)) != NULL) {

        if (entrada->d_type == DT_REG) {  // Se for um arquivo comum (ignora subpastas)

            // Obtemos a extensão (tipo) do arquivo, ex: .jpg, .pdf
            const char *ext = obter_extensao(entrada->d_name);

            // Descobrimos a categoria com base na extensão
            const char *categoria = detectar_categoria(ext);

            // Criamos a pasta dessa categoria (caso ainda não exista)
            criar_pasta(pasta, categoria);

            // Montamos o caminho completo do arquivo de origem
            char origem[512];
            snprintf(origem, sizeof(origem), "%s%c%s", pasta, PATH_SEP, entrada->d_name);

            // Montamos o caminho de destino (dentro da subpasta)
            char destino[512];
            snprintf(destino, sizeof(destino), "%s%c%s%c%s", pasta, PATH_SEP, categoria, PATH_SEP, entrada->d_name);

            // Movemos o arquivo para a pasta correspondente
            mover_arquivo(origem, destino);

            // Mostramos na tela o que foi feito
            printf("Movido: %s → %s\n", entrada->d_name, categoria);
        }
    }

    closedir(dir);  // Fecha a pasta depois de terminar
}

// Função principal do programa
int main(int argc, char *argv[]) {
    // Verifica se o usuário passou o nome da pasta como argumento
    if (argc < 2) {
        printf("Uso: %s <caminho_da_pasta>\n", argv[0]);
        return 1;  // Sai do programa com erro
    }

    // Chama a função para organizar os arquivos na pasta indicada
    organizar_pasta(argv[1]);
    return 0;  // Encerra o programa com sucesso
}
