use renovation;

INSERT INTO project(clientID, contractorID, startDate, estimatedEndDate)
VALUES  (16, 5, '2022-04-01', '2022-05-01'),
        (17, 5, '2022-05-03', '2022-06-15'),
        (18, 5, '2022-06-16', '2022-08-01'),
        (19, 5, '2022-08-02', '2022-09-30'),
        (20, 5, '2022-10-01', '2022-11-30'),
        (26, 6, '2022-04-01', '2022-04-15'),
        (27, 6, '2022-04-16', '2022-05-16'),
        (28, 6, '2022-06-01', '2022-06-30'),
        (29, 6, '2022-07-06', '2022-08-25'),
        (30, 6, '2022-08-25', '2022-10-31');
        
CREATE TABLE material (
    ID int(7) NOT NULL AUTO_INCREMENT,
    supplierID int(7) NOT NULL,
    description varchar(100) NOT NULL,
    cost decimal(8, 2) NOT NULL,
    FOREIGN KEY (supplierId) REFERENCES supplier(ID),
    PRIMARY KEY(ID)
);

INSERT INTO material(description, supplierID, cost)
VALUES  ('72 inch bathroom granite counter top', 1, 800.00),
        ('36 inch bathroom granite counter top', 1, 400.00),
        ('24 inch bathroom granite counter top', 1, 300.00),
        ('72 inch kitchen granite counter top', 1, 800.00),
        ('84 inch kitchen granite counter top', 1, 1000.00),
        ('96 inch kitchen granite counter top', 1, 1200.00),
        ('Small bathroom tile package', 2, 700.00),
        ('Medium bathroom tile package', 2, 900.00),
        ('Large bathroom tile package', 2, 1100.00),
        ('Extra large bathroom tile package', 2, 1500.00),
        ('Single bathroom sink mirror', 4, 200.00),
        ('Double bathroom sink mirrors', 4, 500.00),
        ('Full wall bathroom sink mirror', 4, 700.00),
        ('Half wall shower glass', 3, 700.00),
        ('Full wall shower glass', 3, 1300.00),
        ('Shower glass door 24 inch', 3, 400.00),
        ('Bathroom sink faucet package with separate hot and cold handles', 5, 100.00),
        ('Bathroom sink faucet package with single hot and cold handle', 5, 150.00),
        ('Shower faucet package with single hot and cold', 5, 130.00),
        ('Small bathroom paint package', 6, 400.00),
        ('Medium bathroom paint package', 6, 700.00),
        ('Large bathroom paint package', 6, 1000.00),
        ('Extra large bathroom paint package', 6, 1300.00),
        ('72 inch bathroom quartz counter top', 7, 600.00),
        ('36 inch bathroom quartz counter top', 7, 200.00),
        ('24 inch bathroom quartz counter top', 7, 100.00),
        ('72 inch kitchen quartz counter top', 7, 600.00),
        ('84 inch kitchen quartz counter top', 7, 800.00),
        ('96 inch kitchen quartz counter top', 7, 1000.00),
        ('24 inch square sink',8, 100.00),
        ('24 inch round sink',8, 100.00),
        ('36 inch square sink',8, 150.00),
        ('36 inch round sink',8, 150.00),
        ('Small tub',8, 1000.00),
        ('Medium tub',8, 1200.00),
        ('Large tub',8, 1400.00),
        ('Extra large tub',8, 1800.00),
        ('Small shower insert package', 9, 500.00),
        ('Medium shower insert package', 9, 700.00),
        ('Large shower insert package', 9, 900.00),
        ('Extra large shower insert package', 9, 1100.00);
  
SELECT
    m.description AS Material,
    m.cost AS Cost,
    s.supplierName AS Supplier
FROM material m, supplier s
WHERE m.supplierID = s.ID
ORDER BY Supplier;

CREATE TABLE invoice (
    projectID int(7) NOT NULL,
    materialID int(7) NOT NULL,
    FOREIGN KEY (projectID) REFERENCES project(ID),
    FOREIGN KEY (materialID) REFERENCES material(ID),
    PRIMARY KEY(projectID, materialID)
);
    