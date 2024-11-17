#define BOOST_TEST_MODULE testAlgorithms

#include <boost/test/included/unit_test.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <set>

/**
 * \brief Compara duas strings de entrada para verificar igualdade em estrutura e conteúdo.
 *
 * Esta função realiza a comparação de duas strings formatadas. A estrutura esperada é:
 * 1. Uma palavra inicial, seguida por um número (m1/m2).
 * 2. Um conjunto de palavras (de tamanho m1/m2).
 * 3. Um número adicional (n1/n2), seguido por n1/n2 linhas contendo palavras.
 *
 * A função verifica se:
 * - A palavra inicial e os números m1/n1 são iguais.
 * - Os conjuntos de palavras associados são equivalentes.
 * - As palavras nas linhas subsequentes (como um conjunto) são iguais.
 *
 * \param input1 Primeira string de entrada a ser comparada.
 * \param input2 Segunda string de entrada a ser comparada.
 * 
 * \return Verdadeiro se as duas strings forem estruturalmente e semanticamente iguais; falso caso contrário.
 */
bool compareStrings(const std::string& input1, const std::string& input2) {
	std::istringstream stream1(input1);
	std::istringstream stream2(input2);

	std::string word1, word2;
	stream1 >> word1;
	stream2 >> word2;
	if (word1 != word2) return false;

	int m1, m2;
	stream1 >> m1;
	stream2 >> m2;
	if (m1 != m2) return false;

	std::set<std::string> set1, set2;
	for (int i = 0; i < m1; ++i) {
		stream1 >> word1;
		set1.insert(word1);
	}
	for (int i = 0; i < m2; ++i) {
		stream2 >> word2;
		set2.insert(word2);
	}
	if (set1 != set2) return false;

	int n1, n2;
	stream1 >> n1;
	stream2 >> n2;
	if (n1 != n2) return false;

	std::set<std::string>  allWords1, allWords2;
	std::string line;

	std::getline(stream1, line); 	std::getline(stream2, line);
	for (int i = 0; i < n1; ++i) {
		std::getline(stream1, line);
		std::istringstream lineStream1(line);
		while (lineStream1 >> word1) {
			allWords1.insert(word1);
		}
	}

	for (int i = 0; i < n2; ++i) {
		std::getline(stream2, line);
		std::istringstream lineStream2(line);
		while (lineStream2 >> word2) {
			allWords2.insert(word2);
		}
	}

	return allWords1 == allWords2;

}

/**
 * \brief Lê o conteúdo de um arquivo para uma string.
 *
 * Esta função abre um arquivo no caminho fornecido, lê todo o seu conteúdo e o retorna como uma string.
 * Lança uma exceção se o arquivo não puder ser aberto.
 *
 * \param filePath Caminho para o arquivo a ser lido.
 * \return O conteúdo do arquivo como uma string.
 * 
 * \throws std::runtime_error Se o arquivo não puder ser aberto.
 */
std::string readFile(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file) {
		throw std::runtime_error("Erro ao abrir arquivo: " + filePath);
	}
	std::ostringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

/**
 * \brief Executa um programa externo com uma entrada fornecida e retorna a saída.
 *
 * Esta função cria dois arquivos temporários:
 * 1. `temp_input.txt` para armazenar a entrada.
 * 2. `temp_output.txt` para armazenar a saída gerada pelo programa externo.
 *
 * O programa executável deve estar localizado em `./bin/run.out`. A entrada é redirecionada do arquivo temporário
 * e a saída capturada no arquivo de saída. Após a execução, os arquivos temporários são removidos.
 *
 * \param input A string de entrada que será passada para o programa.
 * \return A saída gerada pelo programa como uma string.
 * 
 * \throws std::runtime_error Se o programa não puder ser executado ou se ocorrer erro na manipulação de arquivos.
 */
std::string runProgram(const std::string& input) {
	const std::string executable = "./bin/run.out";

	const std::string tempInput = "temp_input.txt";
	const std::string tempOutput = "temp_output.txt";

	std::ofstream inputFile(tempInput);
	inputFile << input;
	inputFile.close();

	const std::string command = executable + " < " + tempInput + " > " + tempOutput;
	int retCode = std::system(command.c_str());
	if (retCode != 0) {
		throw std::runtime_error("Erro ao executar o programa.");
	}

	std::string output = readFile(tempOutput);

	std::filesystem::remove(tempInput);
	std::filesystem::remove(tempOutput);

	return output;
}

// Roda os arquivos de teste.
BOOST_AUTO_TEST_CASE(IntegrationTest) {
	namespace fs = std::filesystem;
	const std::string inputsPath = "./tests/inputs";
	const std::string outputsPath = "./tests/outputs";

	for (const auto& inputFile : fs::directory_iterator(inputsPath)) {
		std::string inputFilePath = inputFile.path().string();

		std::string outputFilePath = outputsPath + "/" + inputFile.path().filename().string();

		std::string input = readFile(inputFilePath);
		std::string expectedOutput = readFile(outputFilePath);

		std::string actualOutput = runProgram(input);

		BOOST_CHECK_MESSAGE(
			compareStrings(actualOutput, expectedOutput),
			"Falha no teste para arquivo: " + inputFilePath +
			"\nSaída esperada:\n" + expectedOutput +
			"\nSaída gerada:\n" + actualOutput
		);
	}
}