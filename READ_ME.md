**🧩 Sudoku Web com C++ e WebAssembly**

*Este projeto consiste em um jogo de Sudoku executado diretamente no navegador, onde toda a lógica principal do jogo é implementada em C++ e integrada ao front-end
através de WebAssembly (WASM). A proposta é unir o desempenho e a robustez do C++ com a flexibilidade e acessibilidade da web moderna. O projeto adota uma
arquitetura onde o JavaScript atua principalmente como uma camada de interface e comunicação, enquanto o C++ é responsável por toda a lógica do jogo, como
geração do tabuleiro, validação de jogadas e controle do estado da partida.*

*🎯 O Sudoku foi escolhido por ser um problema clássico que envolve regras bem definidas, validações constantes e manipulação de estados, sendo um ótimo exemplo
para esse tipo de integração. Além do aspecto técnico, o projeto também busca manter uma interface simples, intuitiva e agradável para o usuário final.*

*🛠 A lógica central do jogo foi escrita em C++, garantindo desempenho e organização do código. Esse código é compilado para WebAssembly utilizando o Emscripten,
permitindo sua execução no navegador. No front-end, são utilizados HTML5 e CSS3 para a estrutura e o layout da aplicação, enquanto o JavaScript, com auxílio do
jQuery, é responsável por manipular o DOM, capturar eventos do usuário e realizar a comunicação com o módulo WebAssembly.*

*🧠 Quando o usuário acessa o jogo, o navegador carrega inicialmente a interface web. Em paralelo, o módulo WebAssembly é inicializado. Somente após essa
inicialização as funções C++ ficam disponíveis para o JavaScript. O jogador escolhe a dificuldade do jogo (Fácil, Médio ou Difícil), e essa informação é
repassada ao código C++. A partir disso, o C++ gera um tabuleiro válido, remove números de acordo com a dificuldade selecionada e prepara o estado inicial
da partida. O JavaScript então percorre o tabuleiro célula por célula, consultando o C++ para saber quais valores devem ser exibidos, e desenha visualmente
o tabuleiro na tela. A partir desse ponto, toda interação do jogador — como inserir ou apagar números — é validada pelo C++ antes de ser refletida na interface.*

*🔗 A comunicação entre JavaScript e C++ é feita através do Module.cwrap, fornecido pelo Emscripten. Esse mecanismo permite que funções escritas em C++
sejam chamadas diretamente no JavaScript, como se fossem funções nativas. Essa abordagem garante que nenhuma regra do Sudoku fique duplicada no JavaScript,
evitando inconsistências e facilitando a manutenção do código. Entre as principais funções expostas estão:
-> Inicialização do jogo com base na dificuldade escolhida,
-> Leitura do valor de uma célula específica,
-> Validação e inserção de números,
-> Remoção de jogadas,
-> Verificação de conclusão do jogo
*

*📌 Este projeto vai além de um simples jogo de Sudoku. Ele demonstra como WebAssembly pode ser utilizado de forma prática em aplicações web reais,
trazendo código C++ para o navegador de maneira organizada e eficiente. A separação entre lógica e interface, aliada ao uso de tecnologias modernas, torna
este projeto uma ótima base para estudos, experimentações e futuras expansões.*

*📈 O desenvolvimento deste projeto representou um avanço significativo no meu crescimento técnico e conceitual. Ao integrar C++ com WebAssembly, tive contato
direto com uma abordagem mais próxima de aplicações de baixo nível sendo executadas em um ambiente web, o que ampliou minha visão sobre possibilidades além
do JavaScript tradicional. Durante o processo, foi necessário compreender melhor o ciclo de vida do WebAssembly no navegador, lidar com inicialização assíncrona
do runtime, exportação de funções e comunicação segura entre linguagens diferentes. Isso reforçou conceitos importantes como separação de responsabilidades,
controle de estado e sincronização entre camadas da aplicação. Por fim, este projeto fortaleceu minha capacidade de aprender tecnologias novas de forma prática,
investigar documentação, resolver problemas complexos e transformar uma ideia técnica em uma aplicação funcional.*





