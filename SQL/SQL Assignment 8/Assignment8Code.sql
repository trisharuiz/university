use renovation;

INSERT INTO invoice(projectId, materialId)
VALUES  (1, 5),
        (1, 7),
        (1, 14),
        (10, 1),
        (10, 32),                
        (10, 36),                          
        (15, 17),
        (15, 19),
        (15, 24),
        (15, 32),
        (15, 35),
        (18, 3),
        (18, 20);
        
CREATE VIEW invoiceView
AS SELECT
    concat(cl.firstName, " ", cl.lastName) AS Client,
    concat(c.firstName, " ", c.lastName) AS Contractor, 
    s.supplierName AS Supplier, m.description AS Material, m.cost as Cost
  FROM client cl, contractor c, supplier s, material m, project p, invoice i
  WHERE p.ID = i.projectID
  AND   p.clientID = cl.ID
  AND   p.contractorID = c.ID
  AND   m.ID = i.materialID
  AND   m.supplierID = s.ID
ORDER BY Client;