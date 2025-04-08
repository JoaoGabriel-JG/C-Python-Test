# 🔌 OCPP 1.6 Simulador e Servidor WebSocket

Este projeto simula a comunicação entre um carregador de veículos elétricos (EVSE) usando OCPP 1.6 e um servidor backend via WebSocket.

O repositório contém dois módulos:

-  `server/`: Um servidor WebSocket em **Python**, que responde a mensagens OCPP.
-  `simulator/`: Um simulador de carregador OCPP em **C++**, utilizando a biblioteca [microOCPP](https://github.com/matth-x/MicroOcpp) e [ixwebsocket](https://github.com/machinezone/IXWebSocket).

---

# Instruções de instalação e execução
## Requisitos

### Para o servidor Python

- Python 3.7+
- `pip` (gerenciador de pacotes do Python)

### Para o simulador C++

Você pode escolher **um dos dois caminhos**:

####  Opção A: Visual Studio 2022 (recomendado no Windows)

- Visual Studio com C++ e suporte a CMake
- Git

####  Opção B: CMake + MinGW

- [MinGW-w64](https://www.mingw-w64.org/)
- Git
- [CMake](https://cmake.org/download/)

---

## 🧩 Instalação

### 1. Clone o repositório

### Baixe a dependência ixwebsocket para o simulador

cd simulator
git clone https://github.com/machinezone/IXWebSocket external/ixwebsocket

### Como rodar o servidor (Python)

cd server
python -m venv venv
venv\Scripts\activate        # No Windows
pip install -r requirements.txt
python main.py
O servidor escutará em ws://localhost:9000

Comunicação entre os módulos
O servidor responde às seguintes ações OCPP:
BootNotification

Heartbeat

StartTransaction

MeterValues

StopTransaction

Estrutura da solução

Cada mensagem recebida no servidor é analisada (ação OCPP identificada via índice [2]).

As respostas são formatadas conforme o padrão OCPP (array-based JSON-RPC).

A hora atual (currentTime) é retornada dinamicamente usando o horário UTC real.

O simulador envia mensagens sequenciais simulando o ciclo de carregamento.

Exemplo de fluxo
O simulador conecta via WebSocket ao servidor

Envia BootNotification

Recebe Accepted com currentTime

Envia Heartbeat periodicamente

Inicia uma transação (StartTransaction)

Envia valores periódicos (MeterValues)

Encerra a transação (StopTransaction)

Testado em Windows 10 e 11
Python 3.11
Visual Studio 2022
MinGW-w64 9.0.0