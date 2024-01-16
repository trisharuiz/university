use renovation;

CREATE TABLE project (
    ID int(7) NOT NULL AUTO_INCREMENT,
    clientId int(7) NOT NULL,
    contractorId int(7) NOT NULL,
    startDate timestamp NOT NULL,
    estimatedEndDate timestamp NOT NULL,
    FOREIGN KEY (clientId) REFERENCES client(ID),
    FOREIGN KEY (contractorId) REFERENCES contractor(ID),
    PRIMARY KEY(ID)
);

CREATE TABLE contractorSupplier (
    ID int(7) NOT NULL AUTO_INCREMENT,
    contractorId int(7) NOT NULL,
    supplierId int(7) NOT NULL,
    FOREIGN KEY (contractorId) REFERENCES contractor(ID),
    FOREIGN KEY (supplierId) REFERENCES supplier(ID),
    PRIMARY KEY(ID)
);
