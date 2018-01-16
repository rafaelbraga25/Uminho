-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema scdb
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema scdb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `scdb` DEFAULT CHARACTER SET utf8 ;
USE `scdb` ;

-- -----------------------------------------------------
-- Table `scdb`.`Teacher`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `scdb`.`Teacher` (
  `teacher_ID` VARCHAR(45) NOT NULL,
  `password` VARCHAR(20) NOT NULL,
  PRIMARY KEY (`teacher_ID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `scdb`.`CU`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `scdb`.`CU` (
  `cu_ID` VARCHAR(10) NOT NULL,
  `year` TINYINT NOT NULL,
  `semester` TINYINT NOT NULL,
  PRIMARY KEY (`cu_ID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `scdb`.`Teacher_CU`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `scdb`.`Teacher_CU` (
  `teacher_ID` VARCHAR(45) NOT NULL,
  `cu_ID` VARCHAR(10) NOT NULL,
  PRIMARY KEY (`teacher_ID`, `cu_ID`),
  INDEX `fk_Utilizador_has_UC_UC1_idx` (`cu_ID` ASC),
  INDEX `fk_Utilizador_has_UC_Utilizador_idx` (`teacher_ID` ASC),
  CONSTRAINT `fk_Utilizador_has_UC_Utilizador`
    FOREIGN KEY (`teacher_ID`)
    REFERENCES `scdb`.`Teacher` (`teacher_ID`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Utilizador_has_UC_UC1`
    FOREIGN KEY (`cu_ID`)
    REFERENCES `scdb`.`CU` (`cu_ID`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `scdb`.`Shift`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `scdb`.`Shift` (
  `cu_ID` VARCHAR(10) NOT NULL,
  `shift_ID` VARCHAR(10) NOT NULL,
  `teo` BIT NOT NULL,
  `capacity` INT NOT NULL,
  `numClasses` SMALLINT NOT NULL,
  PRIMARY KEY (`cu_ID`, `shift_ID`),
  INDEX `fk_Turno_UC1_idx` (`cu_ID` ASC),
  CONSTRAINT `fk_Turno_UC1`
    FOREIGN KEY (`cu_ID`)
    REFERENCES `scdb`.`CU` (`cu_ID`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `scdb`.`Timetable`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `scdb`.`Timetable` (
  `cu_ID` VARCHAR(10) NOT NULL,
  `shift_ID` VARCHAR(10) NOT NULL,
  `weekDay` TINYINT NOT NULL,
  `beginningHour` TINYINT NOT NULL,
  `endingHour` TINYINT NOT NULL,
  PRIMARY KEY (`cu_ID`, `shift_ID`, `weekDay`, `beginningHour`, `endingHour`),
  INDEX `fk_Timetable_Shift1_idx` (`cu_ID` ASC, `shift_ID` ASC),
  CONSTRAINT `fk_Timetable_Shift1`
    FOREIGN KEY (`cu_ID` , `shift_ID`)
    REFERENCES `scdb`.`Shift` (`cu_ID` , `shift_ID`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `scdb`.`Student`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `scdb`.`Student` (
  `student_ID` VARCHAR(45) NOT NULL,
  `password` VARCHAR(20) NOT NULL,
  `ws` BIT NOT NULL,
  PRIMARY KEY (`student_ID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `scdb`.`Student_CU`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `scdb`.`Student_CU` (
  `student_ID` VARCHAR(45) NOT NULL,
  `cu_ID` VARCHAR(10) NOT NULL,
  PRIMARY KEY (`student_ID`, `cu_ID`),
  INDEX `fk_Student_has_CU_CU1_idx` (`cu_ID` ASC),
  INDEX `fk_Student_has_CU_Student1_idx` (`student_ID` ASC),
  CONSTRAINT `fk_Student_has_CU_Student1`
    FOREIGN KEY (`student_ID`)
    REFERENCES `scdb`.`Student` (`student_ID`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Student_has_CU_CU1`
    FOREIGN KEY (`cu_ID`)
    REFERENCES `scdb`.`CU` (`cu_ID`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `scdb`.`Student_Shift`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `scdb`.`Student_Shift` (
  `student_ID` VARCHAR(45) NOT NULL,
  `cu_ID` VARCHAR(10) NOT NULL,
  `shift_ID` VARCHAR(10) NOT NULL,
  `missedClasses` SMALLINT NOT NULL,
  PRIMARY KEY (`student_ID`, `cu_ID`, `shift_ID`),
  INDEX `fk_Student_has_Shift_Shift1_idx` (`cu_ID` ASC, `shift_ID` ASC),
  INDEX `fk_Student_has_Shift_Student1_idx` (`student_ID` ASC),
  CONSTRAINT `fk_Student_has_Shift_Student1`
    FOREIGN KEY (`student_ID`)
    REFERENCES `scdb`.`Student` (`student_ID`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Student_has_Shift_Shift1`
    FOREIGN KEY (`cu_ID` , `shift_ID`)
    REFERENCES `scdb`.`Shift` (`cu_ID` , `shift_ID`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `scdb`.`Request`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `scdb`.`Request` (
  `student_ID` VARCHAR(45) NOT NULL,
  `cu_ID` VARCHAR(10) NOT NULL,
  `shift_ID` VARCHAR(10) NOT NULL,
  `ws` BIT NOT NULL,
  `idx` INT NOT NULL,
  PRIMARY KEY (`student_ID`, `cu_ID`, `shift_ID`),
  INDEX `fk_Student_has_Shift1_Shift1_idx` (`cu_ID` ASC, `shift_ID` ASC),
  INDEX `fk_Student_has_Shift1_Student1_idx` (`student_ID` ASC),
  CONSTRAINT `fk_Student_has_Shift1_Student1`
    FOREIGN KEY (`student_ID`)
    REFERENCES `scdb`.`Student` (`student_ID`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Student_has_Shift1_Shift1`
    FOREIGN KEY (`cu_ID` , `shift_ID`)
    REFERENCES `scdb`.`Shift` (`cu_ID` , `shift_ID`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `scdb`.`log`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `scdb`.`log` (
  `cu_ID` VARCHAR(10) NOT NULL,
  `shift_ID` VARCHAR(10) NOT NULL,
  `date` DATETIME NOT NULL,
  `text` TEXT NOT NULL,
  PRIMARY KEY (`cu_ID`, `shift_ID`, `date`))
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
