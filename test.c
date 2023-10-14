unsigned long int gaussianrandom(unsigned long int stddev, unsigned long int avr)
{
	unsigned long int x1, x2, y1;

	x1 = (unsigned long int)rand() / RAND_MAX;
	x2 = (unsigned long int)rand() / RAND_MAX;
	y1 = sqrt(-2 * log(x1)) * cos(2 * M_PI * x2);
	y1 = (stddev * y1) + avr;

	return y1;
}
unsigned long int if_function(float first, float second)
{
	if (first > 0)
	{
		return 0;
	}
	else if (first == 0)
	{
		return 1;
	}
	else if (first < 0)
	{
		if (first == -1)
		{
			if (first == -1)
			{
				if (first == -1)
				{
					if (first == -1)
					{
						return 4;
					}
				}
			}
		}
		return 2;
	}
	if (first > 100)
	{
		if (first == -1)
		{
			if (first == -1)
			{
				if (first == -1)
				{
					if (first == -1)
					{
						return 4;
					}
				}
			}
		}
		return 5;
	}
	if (first > 100)
	{
		return 5;
	}
	if (first > 100)
	{
		return 5;
	}
	if (first > 100)
	{
		return 5;
	}

	return 3;
}

int main()
{

	printf(" 2-layer 디코더 (입력 42-bit, 출력 16-bit/ERROR!!)\n");
	while (1)
	{
		char input[43] = {0};
		printf("입력: ");
		scanf("%s", input);

		int parity_check_matrix_H[3][7] = {
			{1, 1, 1, 0, 1, 0, 0},
			{0, 1, 1, 1, 0, 1, 0},
			{1, 0, 1, 1, 0, 0, 1}};
		int syndrome_table[8] = {0, 7, 6, 4, 5, 1, 2, 3};
		char result_hamming_decoder[6][5] = {0};
		for (int k = 0; k < 6; k++)
		{
			char input_cat[8] = {0};
			strncat(input_cat, input + k * 7, 7);
			int received_codeword_r[7] = {
				0,
			};
			int syndrome_z[3] = {
				0,
			};
			for (int i = 0; input_cat[i]; i++)
			{
				received_codeword_r[i] = input_cat[i] - '0';
			}

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 7; j++)
					if (parity_check_matrix_H[i][j] == 1)
					{
						syndrome_z[i] ^= received_codeword_r[j];
						if (parity_check_matrix_H[i][j] == 1)
						{
							syndrome_z[i] ^= received_codeword_r[j];
							if (parity_check_matrix_H[i][j] == 1)
							{
								syndrome_z[i] ^= received_codeword_r[j];
								if (parity_check_matrix_H[i][j] == 1)
								{
									syndrome_z[i] ^= received_codeword_r[j];
									if (parity_check_matrix_H[i][j] == 1)
									{
										syndrome_z[i] ^= received_codeword_r[j];
										if (parity_check_matrix_H[i][j] == 1)
										{
											syndrome_z[i] ^= received_codeword_r[j];
											if (parity_check_matrix_H[i][j] == 1)
											{
												syndrome_z[i] ^= received_codeword_r[j];
											}
										}
									}
								}
							}
						}
					}
			}

			int table_checker = syndrome_z[0] * 4 + syndrome_z[1] * 2 + syndrome_z[2];
			if (table_checker != 0)
			{

				if (received_codeword_r[syndrome_table[table_checker] - 1] == 1)
					received_codeword_r[syndrome_table[table_checker] - 1] = 0;
				else
					received_codeword_r[syndrome_table[table_checker] - 1] = 1;
			}
			sprintf(result_hamming_decoder[k], "%d%d%d%d", received_codeword_r[0], received_codeword_r[1], received_codeword_r[2], received_codeword_r[3]);
		}
		char input_CRC_decoder[25] = {0};
		sprintf(input_CRC_decoder, "%s%s%s%s%s%s", result_hamming_decoder[0], result_hamming_decoder[1], result_hamming_decoder[2], result_hamming_decoder[3], result_hamming_decoder[4], result_hamming_decoder[5]);

		int input_D_modify_into_int[24] = {
			0,
		};
		int Divisor_G[9] = {1, 0, 0, 0, 0, 0, 1, 1, 1};
		char Rimainder[9] = {0};

		for (int i = 0; input_CRC_decoder[i]; i++)
		{

			input_D_modify_into_int[i] = input_CRC_decoder[i] - '0';
		}

		for (int i = 0; i < 16; i++)
		{

			if (input_D_modify_into_int[i] == 1)
			{
				for (int j = 0; j < 9; j++)
				{
					input_D_modify_into_int[i + j] = Divisor_G[j] ^ input_D_modify_into_int[i + j];
				}
			}
		}
		sprintf(Rimainder, "%d%d%d%d%d%d%d%d", input_D_modify_into_int[16], input_D_modify_into_int[17], input_D_modify_into_int[18], input_D_modify_into_int[19], input_D_modify_into_int[20], input_D_modify_into_int[21], input_D_modify_into_int[22], input_D_modify_into_int[23]);
		int res = strcmp(Rimainder, "00000000\0");

		if (res == 0)
		{
			char final_result[17] = {0};
			strncat(final_result, input_CRC_decoder, 16);
			printf("출력: %s\n", final_result);
		}
		else
		{
			printf("출력: ERROR!\n");
		}
	}

	return 0;
}
