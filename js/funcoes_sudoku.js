// NESTE ARQUIVO ESTÃO TODAS AS FUNÇÕES USADAS NO PROJETO 
// CRIADAS NO ARQUIVO 'FUNCOES_SUDOKU_WEB.H' EM C++
// POSTERIORMENTE EXPORTADAS PARA O WASM NO ARQUIVO 'FUNCOES_EMSCRIPTEN_SUDOKU_WEB.CPP'
// PARA CONECTAR O C++ COM JS DESSE PROJETO

let iniciar_jogo;
let celula_jogada;
let valida_numero_original;
let inserir;
let apagar;
let jogo_finalizado;
let wasm_conectado = false;

Module.onRuntimeInitialized = function(){

    // Estrutura da conexão JS > WASM > C++:
    // nome_da_funcao_js = Module.cwrap(
    //      "nome_da_funcao_c++",
    //      "retorno da funcao no c++",
    //      ["parametros"]  
    // );

    iniciar_jogo = Module.cwrap(
        "iniciar_jogo",
        null,
        ["number"]
    );

    celula_jogada = Module.cwrap(
        "celula_jogada",
        "number",
        ["number","number"]
    );

     valida_numero_original = Module.cwrap(
        "valida_numero_original",
        "number",
        ["number","number"]
     );

     inserir = Module.cwrap(
        "jogar",
        "number",
        ["number","number","number"]
     );

     apagar = Module.cwrap(
        "apagar",
        "number",
        ["number","number"]
     );
     
     jogo_finalizado = Module.cwrap(
        "jogo_finalizado",
        "number",
        []
     );

     wasm_conectado = true;
     $(document).trigger("wasm_conectado");
}

// 2) FUNÇÃO DE REDIRECIONAMENTO PARA A PÁGINA DO TABULEIRO
function redireciona(url_pagina){
    var segundos = 3;
    $('#div_redireciona_texto').css('display','flex');
    $('#div_redireciona_texto').show();
    $('#div_redireciona_contador').css('display','flex');
    $('#div_redireciona_contador').show();
    $('#label_redireciona').text("CARREGANDO SEU JOGO");
    var intervalo = setInterval(function(){

        $('#label_contador').text(segundos);
        segundos--;
        if(segundos <= 0){
            clearInterval(intervalo);
            window.location.href = url_pagina;
        }
    },1000);
}

// 3) FUNÇÃO DE ESPERA, QUE EVITA QUE AS FUNÇÕES RESTANTES SEJAM CHAMADAS ANTES DA CONEXÃO COM O C++
function iniciar_evento_jogo(dificuldade){
    let intervalo = setInterval(() =>{
        if(typeof iniciar_jogo === 'function'){
            clearInterval(intervalo);
            console.log("Wasm conectado");
            iniciar_jogo(parseInt(dificuldade));
            desenhar_tabuleiro('tabuleiro_grade');
        }
    },100);
}

// 4) FUNÇÃO QUE DESENHA O TABULEIRO PRONTO PARA INICIAR O JOGO
function desenhar_tabuleiro(tabuleiro){
    let tabuleiro_novo = $('#'+tabuleiro);
    let valor_celula;
    let indice;

    tabuleiro_novo.empty();

    for(let linha = 0; linha < 9; linha++){
        for(let coluna = 0; coluna < 9; coluna++){
            valor_celula = celula_jogada(linha,coluna);
            indice = $('<div>').addClass('celula').attr('data-linha',linha).attr('data-coluna',coluna);

            if(valor_celula != 0){
                indice.text(valor_celula);
                indice.addClass('celula_fixa');
                if(valida_numero_original(linha, coluna)){
                    indice.addClass('celula_fixa');
                }   
            }

            tabuleiro_novo.append(indice);
        }
    }
}

// 4) FUNÇÃO QUE FAZ A LEITURA DO INDICE CLICADO PELO JOGADOR E VALIDA O NUMERO INSERIDO
function jogada(linha,coluna,numero,tipo_jogada){
    let resultado;
    if(tipo_jogada == 'inserir'){
        resultado = inserir(linha,coluna,numero);
        if(resultado == 1){
            atualizar_celula(linha,coluna);
            return true;
        }
        else{
            $.notify("O número informado não é válido na posição escolhida","error");
            return false;
        }
    }

    else if(tipo_jogada == 'deletar'){
        resultado = apagar(linha,coluna);
        if(resultado == 1){
            atualizar_celula(linha,coluna);
            return true;
        }
        else{
            $.notify("Erro ao deletar o número", "error");
            return false;
        }
    }
}

// 5) FUNÇÃO QUE ATUALIZA VISUALMENTE A CÉLULA APÓS INSERIR UM NÚMERO
function atualizar_celula(linha,coluna){
    let numero = celula_jogada(linha,coluna);
    let celula = $(`.celula[data-linha=${linha}][data-coluna=${coluna}]`);
    if(numero != 0){
        celula.text(numero).addClass('celula_jogador');
    }
    else{
        celula.text('').addClass('celula_jogador');
    }
    $('#modal_insere_numero').modal('hide');
    $('#input_jogada').val('');

}

// 6) VERIFICA SE O TABULEIRO FOI COMPLETADO
function verificar_fim_jogo(){
    if(jogo_finalizado() == 1){
        return true;
    }
    else{
        return false;
    }
}

// 7) RETORNA AO INICIO DA PÁGINA
function retornar_inicio(url_pagina){
    window.location.href = url_pagina;
}