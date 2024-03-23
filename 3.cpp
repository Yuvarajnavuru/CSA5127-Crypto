#include <stdio.h>
#include <ctype.h>
#include <string.h>

char key_matrix[5][5];

void create_key_matrix(char key[]) {
  int i, j, len = strlen(key), k = 0;
  char alphabet[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

  // Remove duplicates from the key
  for (i = 0; i < len; i++) {
    if (key[i] == 'J') {
      key[i] = 'I';
    }
    for (j = i + 1; j < len; j++) {
      if (key[i] == key[j]) {
        key[j] = '\0';
      }
    }
  }

  // Fill the matrix with the key and remaining alphabets
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if (k < len && key[k] != '\0') {
        key_matrix[i][j] = key[k++];
      } else {
        for (int l = 0; l < strlen(alphabet); l++) {
          if (strchr(key, alphabet[l]) == NULL) {
            key_matrix[i][j] = alphabet[l];
            break;
          }
        }
      }
    }
  }
}

int get_index(char ch) {
  int i, j;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if (key_matrix[i][j] == toupper(ch)) {
        return (i * 5) + j;
      }
    }
  }
  return -1;
}

void encrypt(char message[]) {
  int i, len = strlen(message);
  for (i = 0; i < len; i += 2) {
    // Handle double letters
    if (message[i] == message[i + 1]) {
      message[i + 1] = 'X';
    }

    int index1 = get_index(message[i]);
    int index2 = get_index(message[i + 1]);

    // Same row
    if (index1 / 5 == index2 / 5) {
      message[i] = key_matrix[index1 / 5][(index1 + 1) % 5];
      message[i + 1] = key_matrix[index2 / 5][(index2 + 1) % 5];
    } else if (index1 % 5 == index2 % 5) {
      // Same column
      message[i] = key_matrix[(index1 + 1) % 5][index1 % 5];
      message[i + 1] = key_matrix[(index2 + 1) % 5][index2 % 5];
    } else {
      // Rectangle case
      message[i] = key_matrix[index1 / 5][index2 % 5];
      message[i + 1] = key_matrix[index2 / 5][index1 % 5];
    }
  }
}

int main() {
  char key[100], message[100];

  printf("Enter the key: ");
  fgets(key, sizeof(key), stdin);
  key[strcspn(key, "\n")] = '\0'; // Remove newline from key

  printf("Enter the message: ");
  fgets(message, sizeof(message), stdin);
  message[strcspn(message, "\n")] = '\0'; // Remove newline from message

  create_key_matrix(key);

  printf("Key Matrix:\n");
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      printf("%c ", key_matrix[i][j]);
    }
    printf("\n");
  }

  encrypt(message);

  printf("Encrypted message: %s\n", message);

  return 0;
}

