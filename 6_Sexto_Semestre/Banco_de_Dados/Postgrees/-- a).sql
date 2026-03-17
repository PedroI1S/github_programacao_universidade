-- a)
SELECT 
    c.customer_id,
    c.first_name,
    c.last_name,
    c.email,
    a.address,
    a.address2,
    a.district,
    a.postal_code,
    a.phone
FROM public.customer AS c
JOIN public.address  AS a
  ON a.address_id = c.address_id
WHERE c.address_id = 605
ORDER BY c.customer_id;

-- b) 
SELECT
  c.country_id, c.country, c.last_update
FROM public.country AS c
ORDER BY c.last_update DESC, c.country_id ASC;

-- c)
SELECT
  f.film_id, f.title, f.description, f.release_year
FROM public.film AS f
WHERE f.release_year BETWEEN '1940' AND '1970'
ORDER BY f.release_year ASC, f.title ASC; 

-- d)


-- e) Liste o primeiro nome e o email de todos os clientes da loja 1
--    ativoes que foram atualizados no mês 2 de 2006
SELECT
  c.first_name, c.email
FROM public.customer AS c
WHERE 
c.store_id = 1 
AND c.activebool = TRUE 
AND c.last_update >= TIMESTAMP '2006-02-01 00:00:00' 
AND c.last_update < TIMESTAMP '2006-03-01 00:00:00'
ORDER BY c.first_name ASC, c.email ASC;
