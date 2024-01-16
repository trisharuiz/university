CREATE DATABASE  IF NOT EXISTS `renovation` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `renovation`;
-- MySQL dump 10.13  Distrib 8.0.27, for Win64 (x86_64)
--
-- Host: localhost    Database: renovation
-- ------------------------------------------------------
-- Server version	8.0.27

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `citystate`
--

DROP TABLE IF EXISTS `citystate`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `citystate` (
  `city` varchar(90) NOT NULL,
  `state` char(2) NOT NULL,
  `zipCode` char(5) NOT NULL,
  PRIMARY KEY (`zipCode`),
  UNIQUE KEY `zipCode` (`zipCode`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `citystate`
--

LOCK TABLES `citystate` WRITE;
/*!40000 ALTER TABLE `citystate` DISABLE KEYS */;
INSERT INTO `citystate` VALUES ('Piscataway','NJ','08854'),('Lanham','MD','20706'),('Abingdon','VA','24210'),('Clover','SC','29710'),('Duluth','GA','30096'),('Jupiter','FL','33458'),('Nashville','TN','37205'),('Memphis','TN','38117'),('Willoughby','OH','44094'),('Cuyahoga Falls','OH','44223'),('Battle Creek','MI','49016'),('Jefferson','LA','70121'),('Covington','LA','70433'),('Scottsdale','AZ','85260'),('Ontario','CA','91764'),('San Marcos','CA','92078'),('Huntington Beach','CA','92647');
/*!40000 ALTER TABLE `citystate` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `client`
--

DROP TABLE IF EXISTS `client`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `client` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `firstName` varchar(50) NOT NULL,
  `lastName` varchar(50) NOT NULL,
  `address` varchar(90) NOT NULL,
  `zipCode` char(5) NOT NULL,
  `phone` char(10) NOT NULL,
  `email` varchar(90) NOT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `email` (`email`),
  KEY `zipCode` (`zipCode`),
  CONSTRAINT `client_ibfk_1` FOREIGN KEY (`zipCode`) REFERENCES `citystate` (`zipCode`)
) ENGINE=InnoDB AUTO_INCREMENT=36 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `client`
--

LOCK TABLES `client` WRITE;
/*!40000 ALTER TABLE `client` DISABLE KEYS */;
INSERT INTO `client` VALUES (1,'Yvonne','Goodman','12 Creekside St','37205','2025550109','ygoodman@isp.com'),(2,'Dante','Mackenzie','137 Wall St','37205','2025550112','dmackenzie@isp.com'),(3,'Alysha','Rollins','411 Shirley St','37205','2025550115','arollins@isp.com'),(4,'Avaya','Gonzalez','7771 Border Court','37205','2025550119','agonzalez@isp.com'),(5,'Haniya','Kelly','6 South Sulphur Springs Street','37205','2025550121','hkelly@isp.com'),(6,'Nathalie','Chambers','942 New Saddle Drive','29710','2025550122','nchambers@isp.com'),(7,'Daniel','Rollins','9 Wrangler Ave','29710','2025550124','drollins@isp.com'),(8,'Beverley','Mckee','7319 S. Greenview Drive','29710','2025550125','bmckee@isp.com'),(9,'Paris','Lindsey','763 West Mulberry St','29710','2025550132','plindsey@isp.com'),(10,'Umaiza','Melia','545 Ohio Ave','29710','2025550135','umelia@isp.com'),(11,'Nico','Prince','20 Middle River Street','44094','2025550137','nprince@isp.com'),(12,'Javan','Rennie','8112 North Country St','44094','2025550139','jrennie@isp.com'),(13,'Ali','Waters','83 Rockland Lane','44094','2025550144','awaters@isp.com'),(14,'JohnPaul','Clarke','1 Riverside Lane','44094','2025550153','jpcClarke@isp.com'),(15,'Dane','Kaiser','694 Wall Road','44094','2025550155','kdaiser@isp.com'),(16,'Hammad','Newman','9970 State Court','30096','2025550157','hnewman@isp.com'),(17,'Maha','Guthrie','54 Woodsman Drive','30096','2025550161','mguthrie@isp.com'),(18,'Tulisa','Roberts','7174 Studebaker Street','30096','2025550163','troberts@isp.com'),(19,'Robin','Solis','8474 Wentworth Street','30096','2025550164','rsolis@isp.com'),(20,'Kavita','Heath','796 Hartford St','30096','2025550165','kheath@isp.com'),(21,'Meera','White','484 Bridge St','08854','2025550166','mwhite@isp.com'),(22,'Bradlee','Esparza','7031 Gainsway St','08854','2025550173','besparza@isp.com'),(23,'Leilani','Leonard','37 Monroe Street','08854','2025550175','lleonard@isp.com'),(24,'Stefanie','Brook','7990 West Surrey St','08854','2025550179','sbrook@isp.com'),(25,'Grover','Squires','7618 Madison Court','08854','2025550180','gsquires@isp.com'),(26,'Jonathan','Kumar','25 Annadale Court','33458','2025550182','jkumar@isp.com'),(27,'Angus','Neville','9841 Smith Drive','33458','2025550187','aneville@isp.com'),(28,'Uzair','Sparrow','7999 Hall Street','33458','2025550188','usparrow@isp.com'),(29,'Amari','Currie','8411 Pleasant St','33458','2025550194','acurrie@isp.com'),(30,'Imaani','Wallace','33 Pierce Rd','33458','2025550195','iwallace@isp.com'),(31,'Efe','House','97 High Point Street','20706','2025550196','ehouse@isp.com'),(32,'Atticus','Atkinson','66 Harrison Dr','20706','2025550197','aatkinson@isp.com'),(33,'Michelle','Ramirez','370 Hill Field Ave','20706','2025550198','mramirez@isp.com'),(34,'Remy','Hassan','249 Devon Lane','20706','2025550199','rhassan@isp.com'),(35,'Jordana','Beck','7911 Carson Lane','20706','2025550200','jbeck@isp.com');
/*!40000 ALTER TABLE `client` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `contractor`
--

DROP TABLE IF EXISTS `contractor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `contractor` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `firstName` varchar(50) NOT NULL,
  `lastName` varchar(50) NOT NULL,
  `address` varchar(90) NOT NULL,
  `zipCode` char(5) NOT NULL,
  `phone` char(10) NOT NULL,
  `email` varchar(90) NOT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `email` (`email`),
  KEY `zipCode` (`zipCode`),
  CONSTRAINT `contractor_ibfk_1` FOREIGN KEY (`zipCode`) REFERENCES `citystate` (`zipCode`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `contractor`
--

LOCK TABLES `contractor` WRITE;
/*!40000 ALTER TABLE `contractor` DISABLE KEYS */;
INSERT INTO `contractor` VALUES (1,'Igor','Prince','12 Creekside St','92647','2025550109','iprince@renovations.com'),(2,'Dante','Rennie','137 Wall St','38117','2025550112','drennie@renovations.com'),(3,'Thomas','Waters','411 Shirley St','24210','2025550115','twaters@renovations.com'),(4,'Avaya','Clarke','7771 Border Court','92078','2025550119','aclarke@renovations.com'),(5,'Haniya','Kaiser','6 South Sulphur Springs Street','70121','2025550121','hkaiser@renovations.com'),(6,'Victor','Newman','942 New Saddle Drive','70433','2025550122','vnewman@renovations.com'),(7,'Douglas','Guthrie','9 Wrangler Ave','91764','2025550124','dguthrie@renovations.com'),(8,'Brian','Roberts','7319 S. Greenview Drive','44223','2025550125','broberts@renovations.com'),(9,'Paris','Solis','763 West Mulberry St','49016','2025550132','psolis@renovations.com'),(10,'Umaiza','Heath','545 Ohio Ave','85260','2025550135','uheath@renovations.com');
/*!40000 ALTER TABLE `contractor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `contractorsupplier`
--

DROP TABLE IF EXISTS `contractorsupplier`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `contractorsupplier` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `contractorId` int NOT NULL,
  `supplierId` int NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `contractorId` (`contractorId`),
  KEY `supplierId` (`supplierId`),
  CONSTRAINT `contractorsupplier_ibfk_1` FOREIGN KEY (`contractorId`) REFERENCES `contractor` (`ID`),
  CONSTRAINT `contractorsupplier_ibfk_2` FOREIGN KEY (`supplierId`) REFERENCES `supplier` (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=32 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `contractorsupplier`
--

LOCK TABLES `contractorsupplier` WRITE;
/*!40000 ALTER TABLE `contractorsupplier` DISABLE KEYS */;
INSERT INTO `contractorsupplier` VALUES (1,1,1),(2,1,2),(3,1,4),(4,2,2),(5,2,3),(6,2,5),(7,3,4),(8,3,3),(9,3,6),(10,4,3),(11,4,5),(12,4,6),(13,5,5),(14,5,8),(15,5,7),(16,6,6),(17,6,1),(18,6,7),(19,7,7),(20,7,9),(21,7,8),(22,8,8),(23,8,1),(24,8,7),(25,9,9),(26,9,1),(27,9,3),(28,10,9),(29,10,8),(30,10,1),(31,10,6);
/*!40000 ALTER TABLE `contractorsupplier` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `project`
--

DROP TABLE IF EXISTS `project`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `project` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `clientId` int NOT NULL,
  `contractorId` int NOT NULL,
  `startDate` timestamp NOT NULL,
  `estimatedEndDate` timestamp NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `clientId` (`clientId`),
  KEY `contractorId` (`contractorId`),
  CONSTRAINT `project_ibfk_1` FOREIGN KEY (`clientId`) REFERENCES `client` (`ID`),
  CONSTRAINT `project_ibfk_2` FOREIGN KEY (`contractorId`) REFERENCES `contractor` (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `project`
--

LOCK TABLES `project` WRITE;
/*!40000 ALTER TABLE `project` DISABLE KEYS */;
/*!40000 ALTER TABLE `project` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `supplier`
--

DROP TABLE IF EXISTS `supplier`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `supplier` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `supplierName` varchar(50) NOT NULL,
  `address` varchar(90) NOT NULL,
  `zipCode` char(5) NOT NULL,
  `phone` char(10) NOT NULL,
  `email` varchar(90) NOT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `supplierName` (`supplierName`),
  UNIQUE KEY `email` (`email`),
  KEY `zipCode` (`zipCode`),
  CONSTRAINT `supplier_ibfk_1` FOREIGN KEY (`zipCode`) REFERENCES `citystate` (`zipCode`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `supplier`
--

LOCK TABLES `supplier` WRITE;
/*!40000 ALTER TABLE `supplier` DISABLE KEYS */;
INSERT INTO `supplier` VALUES (1,'New Direction Granite','16321 Gothard St. Suite C-F','92647','5626068511','info@new-direction-granite.com'),(2,'Monogram Tile','530 Oak Court Drive Suite 400','38117','9016857167','info@monogram-tile.com'),(3,'Glass Specialties,  Inc','1231 Linda Vista Drive','92078','7607448220','info@glass-specialties.com'),(4,'Dutt and Wagner Mirrors','1142 West Main Street','24210','8006882116','info@dutt-wagner-mirrors.com'),(5,'John E. Koerner Fixtures','4820 Jefferson Hwy','70121','8003331913','info@koerner-fixtures.com'),(6,'Diversified Paint and Supplies LLC','1404 Greengate Drive Suite 300','70433','8009142382','info@diversified-paint.com'),(7,'Ajinomoto Quartz North America','4200 Concours Street Suite 100','91764','9094774700','info@ajinomoto-quartz-na.com'),(8,'Ascot Valley Sinks and Tubs','205 Ascot Pkwy','44223','3303769411','info@ascotvalleysinks.com'),(9,'Kellogg Shower Inserts','P.O. Box CAMB','49016','8009621413','info@kelloggs.com');
/*!40000 ALTER TABLE `supplier` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-02-28 16:07:11
