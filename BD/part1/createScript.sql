-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema eventosdb
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema eventosdb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `eventosdb` DEFAULT CHARACTER SET utf8 ;
USE `eventosdb` ;

-- -----------------------------------------------------
-- Table `eventosdb`.`Pessoa`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `eventosdb`.`Pessoa` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `email` VARCHAR(45) NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `sexo` ENUM('M', 'F') NOT NULL DEFAULT 'F',
  `dataNasc` DATE NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `email_UNIQUE` (`email` ASC))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `eventosdb`.`Evento`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `eventosdb`.`Evento` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `titulo` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `eventosdb`.`Edicao`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `eventosdb`.`Edicao` (
  `nEdicao` INT NOT NULL,
  `eventoID` INT NOT NULL,
  `descricao` VARCHAR(1000) NOT NULL,
  `preco` DECIMAL(4,2) UNSIGNED NOT NULL,
  `lotacao` INT UNSIGNED NOT NULL,
  `inicio` DATETIME NOT NULL,
  `fim` DATETIME NOT NULL,
  `pais` VARCHAR(30) NOT NULL,
  `cidade` VARCHAR(30) NOT NULL,
  `rua` VARCHAR(50) NOT NULL,
  `nMulheres` INT NOT NULL DEFAULT 0,
  `nHomens` INT NOT NULL DEFAULT 0,
  `menores18` INT NOT NULL DEFAULT 0,
  `pessoas18_25` INT NOT NULL DEFAULT 0,
  `pessoas25_30` INT NOT NULL DEFAULT 0,
  CHECK (fim > inicio AND 
	numero_de_homens + numero_de_mulheres >= 
	pessoas_menores_18 + pessoas_18_25 + pessoas_25_30),
  INDEX `fk_Edicao_de_Evento_Evento1_idx` (`eventoID` ASC),
  PRIMARY KEY (`nEdicao`, `eventoID`),
  CONSTRAINT `fk_Edicao_de_Evento_Evento1`
    FOREIGN KEY (`eventoID`)
    REFERENCES `eventosdb`.`Evento` (`id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `eventosdb`.`Organizacao`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `eventosdb`.`Organizacao` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `email` VARCHAR(45) NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `pais` VARCHAR(30) NOT NULL,
  `cidade` VARCHAR(30) NOT NULL,
  `rua` VARCHAR(50) NOT NULL,
  `nMulheres` INT NOT NULL DEFAULT 0,
  `nHomens` INT NOT NULL DEFAULT 0,
  `menores18` INT NOT NULL DEFAULT 0,
  `pessoas18_25` INT NOT NULL DEFAULT 0,
  `pessoas25_30` INT NOT  NULL DEFAULT 0,
  CHECK (nHomens + nMulheres >= 
	menores18 + pessoas18_25 + pessoas25_30),
  PRIMARY KEY (`id`),
  UNIQUE INDEX `email_UNIQUE` (`email` ASC))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `eventosdb`.`Foto`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `eventosdb`.`Foto` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `pessoaID` INT NOT NULL,
  `foto` VARCHAR(1000) NOT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_foto_Pessoa1_idx` (`pessoaID` ASC),
  UNIQUE INDEX `foto_UNIQUE` (`foto` ASC),
  CONSTRAINT `fk_foto_Pessoa1`
    FOREIGN KEY (`pessoaID`)
    REFERENCES `eventosdb`.`Pessoa` (`id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `eventosdb`.`PessoaVaiEdicao`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `eventosdb`.`PessoaVaiEdicao` (
  `pessoaID` INT NOT NULL,
  `eventoID` INT NOT NULL,
  `nEdicao` INT NOT NULL,
  PRIMARY KEY (`pessoaID`, `eventoID`, `nEdicao`),
  INDEX `fk_Pessoa_has_Edicao_de_Evento_Pessoa1_idx` (`pessoaID` ASC),
  INDEX `fk_Pessoa_has_Edicao_de_Evento_EdicaoEvento1_idx` (`eventoID` ASC, `nEdicao` ASC),
  CONSTRAINT `fk_Pessoa_has_Edicao_de_Evento_Pessoa1`
    FOREIGN KEY (`pessoaID`)
    REFERENCES `eventosdb`.`Pessoa` (`id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Pessoa_has_Edicao_de_Evento_EdicaoEvento1`
    FOREIGN KEY (`eventoID` , `nEdicao`)
    REFERENCES `eventosdb`.`Edicao` (`eventoID` , `nEdicao`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `eventosdb`.`OrganizacaoEvento`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `eventosdb`.`OrganizacaoEvento` (
  `orgID` INT NOT NULL,
  `eventoID` INT NOT NULL,
  PRIMARY KEY (`orgID`, `eventoID`),
  INDEX `fk_Organizacao_de_Eventos_has_Evento_Evento1_idx` (`eventoID` ASC),
  INDEX `fk_Organizacao_de_Eventos_has_Evento_Organizacao_de_Eventos_idx` (`orgID` ASC),
  CONSTRAINT `fk_Organizacao_de_Eventos_has_Evento_Organizacao_de_Eventos1`
    FOREIGN KEY (`orgID`)
    REFERENCES `eventosdb`.`Organizacao` (`id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Organizacao_de_Eventos_has_Evento_Evento1`
    FOREIGN KEY (`eventoID`)
    REFERENCES `eventosdb`.`Evento` (`id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `eventosdb`.`Contacto`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `eventosdb`.`Contacto` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `orgID` INT NOT NULL,
  `contacto` VARCHAR(45) NOT NULL,
  `tipo` ENUM('telefone', 'telemovel', 'website') NOT NULL DEFAULT 'telemovel',
  PRIMARY KEY (`id`),
  INDEX `fk_contacto_Organizacao_de_Eventos1_idx` (`orgID` ASC),
  UNIQUE INDEX `descricao_UNIQUE` (`contacto` ASC),
  CONSTRAINT `fk_contacto_Organizacao_de_Eventos1`
    FOREIGN KEY (`orgID`)
    REFERENCES `eventosdb`.`Organizacao` (`id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
