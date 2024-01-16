use renovation;

INSERT INTO project(clientID, contractorID, startDate, estimatedEndDate)
VALUES  (1, 2, '2022-04-01', '2022-05-01'),
        (2, 2, '2022-05-03', '2022-06-15'),
        (3, 2, '2022-06-16', '2022-08-01'),
        (4, 2, '2022-08-02', '2022-09-30'),
        (5, 2, '2022-10-01', '2022-11-30'),
        (11, 8, '2022-04-01', '2022-04-15'),
        (12, 8, '2022-04-16', '2022-05-16'),
        (13, 8, '2022-06-01', '2022-06-30'),
        (14, 8, '2022-07-06', '2022-08-25'),
        (15, 8, '2022-08-25', '2022-10-31');

CREATE VIEW scheduleView
AS SELECT
    concat(c.firstName, " ", c.lastName) AS Contractor, concat(cl.firstName, " ", cl.lastName) AS Client,
    p.startDate AS Start, p.estimatedEndDate AS Completion
  FROM contractor c, client cl, project p
  WHERE p.clientID = cl.ID
  AND   p.contractorID = c.ID
ORDER BY Contractor, Start;