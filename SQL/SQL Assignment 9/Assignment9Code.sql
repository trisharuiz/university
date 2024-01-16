use renovation;

DELIMITER $$
DROP PROCEDURE IF EXISTS printInvoice$$

CREATE PROCEDURE printInvoice (IN clientId int, INOUT invoice varchar(4000))
BEGIN

    DECLARE v_finished INTEGER DEFAULT 0;
    DECLARE v_lines varchar(100) DEFAULT "----------------------------------------------------------------------------------------------------";
    DECLARE v_clientFirst varchar(100) DEFAULT "";
    DECLARE v_clientLast varchar(100) DEFAULT "";
    DECLARE v_contractorFirst varchar(100) DEFAULT "";
    DECLARE v_contractorLast varchar(100) DEFAULT ""; 
    DECLARE v_supplier varchar(100) DEFAULT "";
    DECLARE v_material varchar(100) DEFAULT "";
    DECLARE v_cost decimal(8,2) DEFAULT 0.0;
    DECLARE v_sum decimal(8,2) DEFAULT 0.0;
    DECLARE v_count integer DEFAULT 0;
    
    DEClARE client_cursor CURSOR FOR 
        SELECT
            cl.firstName, cl.lastName, c.firstName, c.lastName,
            RPAD(s.supplierName, 35, ' '), RPAD(m.description, 65, ' '), m.cost
        FROM
            client cl, contractor c, supplier s, material m, project p, invoice i
        WHERE cl.ID = clientID
        AND   p.ID = i.projectID
        AND   p.clientID = cl.ID
        AND   p.contractorID = c.ID
        AND   m.ID = i.materialID
        AND   m.supplierID = s.ID;

    DECLARE CONTINUE HANDLER 
        FOR NOT FOUND SET v_finished = 1;
        
    OPEN client_cursor;


    get_client: LOOP

        FETCH client_cursor INTO v_clientFirst, v_clientLast, v_contractorFirst, v_contractorLast, v_supplier, v_material, v_cost;

        IF v_finished = 1 THEN 
            LEAVE get_client;
        END IF;

        SET v_count = v_count + 1;

        IF v_count = 1 THEN
            SET invoice = CONCAT(invoice, '\nINVOICE PREPARED FOR:\n\n');
            SET invoice = CONCAT(invoice, '\n', v_lines, '\n');     
            SET invoice = CONCAT(invoice, '\nCONTRACTOR\n\n');
            SET invoice = CONCAT(invoice, v_contractorFirst, ' ', v_contractorLast); 
            SET invoice = CONCAT(invoice, '\n', v_lines, '\n');     
            SET invoice = CONCAT(invoice, '\nCUSTOMER\n\n');
            SET invoice = CONCAT(invoice, v_clientFirst, ' ', v_clientLast);
            SET invoice = CONCAT(invoice, '\n', v_lines, '\n');
            SET invoice = CONCAT(invoice, 'SUPPLIER', char(9), char(9), char(9), '   MATERIAL', char(9), char(9), char(9), char(9), char(9), char(9), char(9), '     COST');
            SET invoice = CONCAT(invoice, '\n', v_lines, '\n');  
            SET invoice = CONCAT(invoice, v_supplier, v_material, '$', v_cost); 
            SET v_sum = v_sum + v_cost;

        ELSE
            SET invoice = CONCAT(invoice, '\n');  
            SET invoice = CONCAT(invoice, v_supplier, v_material, '$', v_cost);
            SET v_sum = v_sum + v_cost;
        END IF;

    END LOOP get_client;

    SET invoice = CONCAT(invoice, '\n\n', char(9), char(9), char(9), char(9), char(9), char(9), char(9), 'TOTAL', char(9), char(9), char(9), char(9), '   $', v_sum, '\n');

    CLOSE client_cursor;

END$$
DELIMITER ;