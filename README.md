# Criptografia-homomorfica-usando-paillier

Descrição Geral
O documento explica a implementação de um código para criptografia e descriptografia de strings utilizando o algoritmo de criptografia homomórfica Paillier. Esse tipo de criptografia permite a execução de operações matemáticas diretamente em dados criptografados, sem a necessidade de descriptografá-los, o que é particularmente útil para preservar a privacidade dos dados em ambientes sensíveis.

Funcionalidades do Código

Criptografia de String: O código recebe uma string de entrada, converte cada caractere para seu valor numérico correspondente (usando a tabela ASCII), e então criptografa esse valor utilizando a chave pública gerada pelo algoritmo Paillier.

Descriptografia de String: Para descriptografar, o código converte cada valor criptografado de volta para seu valor numérico original utilizando a chave privada correspondente. Esse valor numérico é então convertido de volta para o caractere ASCII original.

Principais Componentes e Requisitos

Geração de Chaves: O código gera um par de chaves pública e privada de 512 bits, usando a biblioteca Paillier.
Funções de Criptografia e Descriptografia: São fornecidas funções para criptografar e descriptografar strings inteiras, com tratamento de cada caractere individualmente.
Função de Geração de Aleatórios: Para garantir a segurança, utiliza-se a função paillier_get_rand_devurandom, que obtém números aleatórios do dispositivo /dev/urandom.
Requisitos para Execução

Instalação da biblioteca GMP (GNU Multiple Precision Arithmetic Library).
Instalação da biblioteca Paillier, que implementa o algoritmo de criptografia homomórfica.
Compilador C compatível (como gcc) e um ambiente de desenvolvimento configurado corretamente para incluir essas bibliotecas.
Outras Observações

O código inclui tratamento de erros para falhas em alocações de memória e erros de criptografia/descriptografia.
Ele demonstra como utilizar o algoritmo Paillier para operações homomórficas básicas com strings, servindo como um exemplo introdutório.
