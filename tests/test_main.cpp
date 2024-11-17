#define BOOST_TEST_MODULE testAlgorithms

#include <boost/test/included/unit_test.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <set>

bool compareStrings(const std::string& input1, const std::string& input2) {
	std::istringstream stream1(input1);
	std::istringstream stream2(input2);

	// Primeira parte: comparar a primeira palavra
	std::string word1, word2;
	stream1 >> word1;
	stream2 >> word2;
	if (word1 != word2) return false;

	// Segunda parte: comparar o número m
	int m1, m2;
	stream1 >> m1;
	stream2 >> m2;
	if (m1 != m2) return false;

	// Comparar as m palavras únicas
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

	// Terceira parte: comparar o número n
	int n1, n2;
	stream1 >> n1;
	stream2 >> n2;
	if (n1 != n2) return false;

	// Comparar as palavras distintas em cada grupo de n linhas
	std::set<std::string>  allWords1, allWords2;
	std::string line;

	std::getline(stream1, line); // Consumir o caractere de nova linha após o número n1
	std::getline(stream2, line); // Consumir o caractere de nova linha após o número n2

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

// Função auxiliar para ler o conteúdo de um arquivo
std::string readFile(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file) {
		throw std::runtime_error("Erro ao abrir arquivo: " + filePath);
	}
	std::ostringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

// Função auxiliar para executar o programa com entrada e capturar a saída
std::string runProgram(const std::string& input) {
	// Caminho para o executável
	const std::string executable = "./bin/run.out";

	// Cria arquivos temporários para entrada e saída
	const std::string tempInput = "temp_input.txt";
	const std::string tempOutput = "temp_output.txt";

	// Escreve a entrada no arquivo temporário
	std::ofstream inputFile(tempInput);
	inputFile << input;
	inputFile.close();

	// Executa o comando e redireciona a saída
	const std::string command = executable + " < " + tempInput + " > " + tempOutput;
	int retCode = std::system(command.c_str());
	if (retCode != 0) {
		throw std::runtime_error("Erro ao executar o programa.");
	}

	// Lê a saída do arquivo temporário
	std::string output = readFile(tempOutput);

	// Remove arquivos temporários
	std::filesystem::remove(tempInput);
	std::filesystem::remove(tempOutput);

	return output;
}

BOOST_AUTO_TEST_CASE(IntegrationTest) {
	namespace fs = std::filesystem;
	const std::string inputsPath = "./tests/inputs";
	const std::string outputsPath = "./tests/outputs";

	// Itera sobre os arquivos da pasta de entrada
	for (const auto& inputFile : fs::directory_iterator(inputsPath)) {
		std::string inputFilePath = inputFile.path().string();

		// Calcula o caminho do arquivo de saída correspondente
		std::string outputFilePath = outputsPath + "/" + inputFile.path().filename().string();

		// Lê a entrada e a saída esperada
		std::string input = readFile(inputFilePath);
		std::string expectedOutput = readFile(outputFilePath);

		// Executa o programa e captura a saída
		std::string actualOutput = runProgram(input);

		// Compara a saída gerada com a saída esperada
		BOOST_CHECK_MESSAGE(
			//actualOutput == expectedOutput,
			compareStrings(actualOutput, expectedOutput),
			"Falha no teste para arquivo: " + inputFilePath +
			"\nSaída esperada:\n" + expectedOutput +
			"\nSaída gerada:\n" + actualOutput
		);
	}
}