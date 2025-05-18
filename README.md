# 🧹 Organizador de Arquivos - Simples e Automático

Este é um programa open source, leve e prático, criado para organizar automaticamente arquivos dentro de uma pasta (como a pasta **Downloads**), separando-os por tipo em subpastas como: **Imagens**, **Documentos**, **Músicas**, etc.

## 💡 Objetivo

Criar uma ferramenta útil para qualquer pessoa — mesmo que não tenha conhecimento técnico — organizar arquivos de forma rápida e eficiente, sem anúncios, sem pegadinhas e sem precisar pagar por isso.

---

## ⚙️ Como funciona

O programa:

1. Lê todos os arquivos dentro da pasta indicada.
2. Verifica a extensão de cada arquivo (como `.jpg`, `.pdf`, `.mp3`, etc).
3. Cria subpastas com nomes como:
   - `Imagens`
   - `Documentos`
   - `Músicas`
   - `Outros`
4. Move os arquivos para suas respectivas subpastas.

---

## 📥 Exemplo de uso

Suponha que sua pasta **Downloads** esteja cheia de arquivos misturados. Basta executar:

```bash
./organizador ~/Downloads
```
E o programa organizará assim:
```
Downloads/
├── Imagens/
│   └── foto.jpg
├── Documentos/
│   └── contrato.pdf
├── Músicas/
│   └── musica.mp3
├── Outros/
│   └── arquivo.zip
```

🖥️ Como compilar
🔹 No Linux ou macOS

```
gcc -o organizador main.c
./organizador /caminho/da/pasta
```

🔹 No Windows (com MinGW)

```
gcc -o organizador.exe main.c
organizador.exe C:\Users\SeuNome\Downloads
```

📁 Tipos de arquivos reconhecidos
| Categoria  | Extensões suportadas |
| ---------- | -------------------- |
| Imagens    | `.jpg`, `.png`       |
| Documentos | `.pdf`, `.docx`      |
| Músicas    | `.mp3`               |
| Outros     | Qualquer outro tipo  |

Você pode expandir facilmente adicionando mais tipos no código.

🛡️ Licença
Este projeto está licenciado sob a MIT License — você é livre para usar, modificar e distribuir!

🧠 Futuras melhorias
- Evitar sobrescrever arquivos com nomes repetidos
- Interface gráfica simples para usuários iniciantes
- Suporte a mais formatos de arquivos
- Barra de progresso ou contador visual

🤝 Contribuições
Contribuições são muito bem-vindas! Sinta-se à vontade para abrir issues, enviar pull requests, ou sugerir melhorias.

✨ Sobre o autor
Desenvolvido por Jonas com a missão de criar ferramentas simples, eficientes e honestas para o dia a dia.
