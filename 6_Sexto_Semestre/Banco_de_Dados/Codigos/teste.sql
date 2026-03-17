SELECT version();

-- Criando uma tabela de exemplo para alunos
CREATE TABLE alunos (
    id SERIAL PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE
);

-- Inserindo alguns dados
INSERT INTO alunos (nome, email) VALUES
('João Silva', 'joao.silva@email.com'),
('Maria Oliveira', 'maria.oliveira@email.com');

-- Consultando os dados inseridos
SELECT id, nome, email FROM alunos;