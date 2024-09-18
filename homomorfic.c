#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include "paillier.h"  // Certifique-se de que a biblioteca Paillier instalada corretamente

// Função para gerar números aleatórios a partir de /dev/urandom
void paillier_get_rand_devurandom(void *buf, int len) {
    FILE *f = fopen("/dev/urandom", "r");
    if (f == NULL) {
        perror("Erro ao abrir /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(buf, 1, len, f);
    fclose(f);
}

// Função para criptografar uma string
paillier_ciphertext_t** encrypt_string(const char *input, paillier_pubkey_t *pub) {
    int len = strlen(input);
    paillier_ciphertext_t **enc_data = malloc(len * sizeof(paillier_ciphertext_t*));

    if (!enc_data) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < len; i++) {
        // Converte cada caractere para o valor numérico (ASCII)
        paillier_plaintext_t *m = paillier_plaintext_from_ui((unsigned long)input[i]);
        if (!m) {
            fprintf(stderr, "Erro ao criar o plaintext para o caractere: %c\n", input[i]);
            exit(EXIT_FAILURE);
        }

        // Criptografa o caractere
        enc_data[i] = paillier_enc(NULL, pub, m, paillier_get_rand_devurandom);
        if (enc_data[i] == NULL) {
            fprintf(stderr, "Erro ao criptografar o caractere: %c\n", input[i]);
            paillier_freeplaintext(m);  // Liberar memória antes de sair
            exit(EXIT_FAILURE);
        }
        
        // Liberando memória do plaintext
        paillier_freeplaintext(m);
    }

    return enc_data;
}

// Função para descriptografar uma string
char* decrypt_string(paillier_ciphertext_t **enc_data, int len, paillier_pubkey_t *pub, paillier_prvkey_t *prv) {
    char *output = malloc((len + 1) * sizeof(char));
    if (!output) {
        fprintf(stderr, "Erro de alocação de memória para a string descriptografada.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < len; i++) {
        // Descriptografa o valor
        paillier_plaintext_t *dec = paillier_dec(NULL, pub, prv, enc_data[i]);
        if (dec == NULL) {
            fprintf(stderr, "Erro ao descriptografar o dado.\n");
            exit(EXIT_FAILURE);
        }

        // Converte o valor numérico de volta para caractere
        output[i] = (char)mpz_get_ui(dec->m);

        // Liberando memória
        paillier_freeplaintext(dec);
    }

    output[len] = '\0';  // Finalizando a string
    return output;
}

int main() {
    // Geração das chaves pública e privada
    paillier_pubkey_t *pub;
    paillier_prvkey_t *prv;

    // Gerando as chaves (tamanho de 512 bits)
    paillier_keygen(512, &pub, &prv, paillier_get_rand_devurandom);

    if (pub == NULL || prv == NULL) {
        fprintf(stderr, "Erro na geração das chaves.\n");
        exit(EXIT_FAILURE);
    }

    // Entrada do usuário (uma string, por exemplo)
    char input[256];
    printf("Digite uma string para criptografar: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // Remove a nova linha do input

    // Criptografando a string
    int len = strlen(input);
    paillier_ciphertext_t **enc_data = encrypt_string(input, pub);

    // Realizando a descriptografia
    char *decrypted_data = decrypt_string(enc_data, len, pub, prv);

    
    printf("String descriptografada: %s\n", decrypted_data);

    
    for (int i = 0; i < len; i++) {
        paillier_freeciphertext(enc_data[i]);
    }
    free(enc_data);
    free(decrypted_data);
    paillier_freepubkey(pub);
    paillier_freeprvkey(prv);

    return EXIT_SUCCESS;
}
