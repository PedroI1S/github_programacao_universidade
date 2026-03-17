--1. Considerando o banco de dados dvdrental faça as seguintes consultas em Postgre SQL sem usar subselects:

--a) Relação que retorne (language, title, release_year, rating) dos filmes de nacionalidade francesa, japonesa e italiana em ordem de nacionalidade e nome do filme;
SELECT l.name as language, f.title, f.release_year, f.rating
FROM film f
JOIN language l ON f.language_id = l.language_id
WHERE l.name IN ('French', 'Japanese', 'Italian')
ORDER BY l.name, f.title;

--b) Faturamento total (amount) agrupado por cliente do filme (mostrar código da cliente, nome completo do cliente e valor total) em ordem descendente do valor total;
SELECT c.customer_id, 
       c.first_name || ' ' || c.last_name as full_name,
       SUM(p.amount) total_amount
FROM customer c
JOIN payment p ON c.customer_id = p.customer_id
GROUP BY c.customer_id, full_name
ORDER BY total_amount DESC;

--c) Relação dos 5 filmes mais locados (quantas vezes) (mostrar film_id, title e a quantidade de locações realizadas por filme.
SELECT f.film_id, 
  f.title,
  COUNT(rental_id) as rental_count
FROM film f
JOIN inventory i ON f.film_id = i.film_id
JOIN rental r ON i.inventory_id = r.inventory_id
GROUP BY f.film_id, f.title
ORDER BY rental_count DESC
LIMIT 5;

--d) Mostrar o número de locações feitas e o total faturado por cada colaborador - nome completo (staf), por ano e por mês.
SELECT s.first_name || ' ' || s.last_name full_name,
  EXTRACT(YEAR FROM r.rental_date) rental_year,
  EXTRACT(MONTH FROM r.rental_date) rental_month,
  COUNT(r.rental_id) total_rentals,
  SUM(p.amount) AS total_revenue
FROM public.staff s
JOIN rental r ON s.staff_id = r.staff_id
JOIN payment p ON r.rental_id = p.rental_id
GROUP BY full_name, rental_year, rental_month
ORDER BY full_name, rental_year, rental_month;

--e) Usando junção natural à esquerda, verificar se existe algum filme que não foi locado em 07/2006 (customer x rental). Listar o código e o nome dos filmes em ordem alfabética.
SELECT f.film_id, f.title
FROM public.film AS f
LEFT JOIN public.inventory AS i ON f.film_id = i.film_id
LEFT JOIN public.rental AS r ON i.inventory_id = r.inventory_id
     AND r.rental_date >= TIMESTAMP '2006-07-01 00:00:00' 
     AND r.rental_date < TIMESTAMP '2006-08-01 00:00:00' 
WHERE r.rental_id IS NULL
ORDER BY f.title; 

--f) Crie uma visão de nove view_rentals que retorne uma tabela que mostre o nome do cliente completo e a data da locaçãonoformato DD/MM/YYYY. Considere apenas as datas (excluindo as horas). Não poderão aparecer linhas duplicadas. Dica:
-- pesquise como trazer linhas distintas
CREATE OR REPLACE VIEW view_rentals AS
SELECT DISTINCT c.first_name || ' ' || c.last_name as full_name,
  TO_CHAR(r.rental_date, 'DD/MM/YYYY') rental_date
FROM customer c
JOIN rental r ON c.customer_id = r.customer_id;

SELECT * FROM view_rentals ORDER BY full_name, rental_date;

--g) Crie uma tabela de nome resumo(ano int primary key, totalfaturado numeric(15,2) default 0) e uma trigger para a tabelapayment, de sorte que a cada INSERÇÃO, o valor do amount seja adicionado ao respectivo ano nesta tabela. Casooanoaindanão exista na tabela de resumo ele deve ser criado pela trigger.
CREATE TABLE resumo (
  ano INT PRIMARY KEY,
  totalfaturado NUMERIC(15,2) DEFAULT 0
);

CREATE FUNCTION atualizar_resumo()
RETURNS TRIGGER AS $$
BEGIN
  IF EXISTS (SELECT 1 FROM resumo WHERE ano = EXTRACT(YEAR FROM NEW.payment_date)) THEN
    UPDATE resumo
    SET totalfaturado = totalfaturado + NEW.amount
    WHERE ano = EXTRACT(YEAR FROM NEW.payment_date);
  ELSE
    INSERT INTO resumo (ano, totalfaturado)
    VALUES (EXTRACT(YEAR FROM NEW.payment_date), NEW.amount);
  END IF;
  RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_atualizar_resumo
AFTER INSERT ON payment
FOR EACH ROW
EXECUTE FUNCTION atualizar_resumo();

--h) Crie uma função que retorne a porcentagem de clientes que alugaram filmes no ano informado como parâmetro na função.
CREATE FUNCTION porcentagem_clientes_ano(ano INT)
RETURNS NUMERIC AS $$
DECLARE
  total_clientes INT;
  clientes_que_alugaram INT;
  porcentagem NUMERIC;
BEGIN
    SELECT COUNT(*) INTO total_clientes FROM customer;
    SELECT COUNT(DISTINCT r.customer_id) INTO clientes_que_alugaram
    FROM rental r
    WHERE EXTRACT(YEAR FROM r.rental_date) = ano;
    
    IF total_clientes = 0 THEN
        RETURN 0;
    END IF; 
    
    porcentagem := (clientes_que_alugaram::NUMERIC / total_clientes::NUMERIC) * 100;
    RETURN porcentagem;
END;
$$ LANGUAGE plpgsql;

--2. Resolva os seguintes exercícios usando álgebra relacional:

--a) Relação de cópias (inventory) existentes por filme. Mostrar o id do filme, o título, o número da cópia e o número da loja onde ela está fisicamente.
-- π film_id, title, inventory_id, store_id (film ⋈ inventory)

--b) Relação usando contendo o primeiro nome e segundo nome dos clientes (customer) de outros países, menos dos EUA, que alugaram filmes de língua inglesa.
-- π first_name, last_name (σ country≠'United States' ∧ language='English' (customer ⋈ address ⋈ city ⋈ country ⋈ rental ⋈ inventory ⋈ film ⋈ language))






