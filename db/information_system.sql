-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Dec 25, 2020 at 12:06 PM
-- Server version: 5.7.31
-- PHP Version: 7.3.21

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `information_system`
--

-- --------------------------------------------------------

--
-- Table structure for table `operations`
--

DROP TABLE IF EXISTS `operations`;
CREATE TABLE IF NOT EXISTS `operations` (
  `operation_id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `payer_name` varchar(32) NOT NULL,
  `receiver_name` varchar(32) NOT NULL,
  `source_number` int(8) UNSIGNED NOT NULL,
  `destination_number` int(8) UNSIGNED NOT NULL,
  `sum` double UNSIGNED NOT NULL,
  `date_time` datetime NOT NULL,
  PRIMARY KEY (`operation_id`)
) ENGINE=MyISAM AUTO_INCREMENT=20 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `operations`
--

INSERT INTO `operations` (`operation_id`, `payer_name`, `receiver_name`, `source_number`, `destination_number`, `sum`, `date_time`) VALUES
(1, 'Vernon Garrard', 'Libby Mann', 76078778, 50500982, 32.11, '2020-09-02 10:34:19'),
(2, 'Kathleen Samuels', 'Enola Teel', 12085274, 28429995, 15.8, '2020-09-04 15:17:49'),
(3, 'Alease Garret', 'Estella Garry', 91256723, 96717347, 49.07, '2020-09-05 18:23:50'),
(4, 'Racquel Seward', 'Luana Howard', 79643296, 51582075, 23.54, '2020-09-08 08:05:34'),
(5, 'Sandy Martel', 'Braith Williams', 11502234, 52304722, 67.12, '2020-09-11 19:23:08'),
(9, 'Harvie Miller', 'Sienna Dawson', 33570323, 82609900, 8.98, '2020-09-20 18:30:44'),
(8, 'Luvenia Goodman', 'Jaycob Falconer', 30091363, 29123692, 45.21, '2020-09-18 07:36:11'),
(7, 'Mack Bell', 'Stew Devereux', 67177386, 39747563, 71.03, '2020-09-17 15:16:13'),
(6, 'Chandler Eads', 'Hervey Swift', 57319164, 44174553, 23.48, '2020-09-13 08:43:44'),
(10, 'Lizette Shearer', 'Laryn Davis', 93630793, 47502275, 19.62, '2020-09-22 19:15:38');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
