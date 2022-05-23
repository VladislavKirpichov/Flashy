-- phpMyAdmin SQL Dump
-- version 4.9.5
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: May 22, 2022 at 06:54 PM
-- Server version: 5.7.24
-- PHP Version: 7.4.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `flashy`
--

-- --------------------------------------------------------

--
-- Table structure for table `page`
--

CREATE TABLE `page` (
  `id` int(11) UNSIGNED NOT NULL,
  `userID` int(11) UNSIGNED NOT NULL,
  `title` varchar(100) NOT NULL,
  `createdTime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updatedTime` timestamp NULL DEFAULT NULL,
  `lastVisited` timestamp NULL DEFAULT NULL,
  `file` varchar(200) CHARACTER SET utf8mb4 NOT NULL,
  `mime` varchar(10) NOT NULL,
  `url` varchar(200) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `page`
--

INSERT INTO `page` (`id`, `userID`, `title`, `createdTime`, `updatedTime`, `lastVisited`, `file`, `mime`, `url`) VALUES
(1, 4, '', '2022-05-11 16:06:47', NULL, NULL, '', '', ''),
(2, 5, '', '2022-05-11 16:48:31', NULL, NULL, '', '', ''),
(3, 4, '', '2022-05-11 16:48:48', NULL, NULL, '', '', ''),
(5, 7, '', '2022-05-11 18:08:52', NULL, NULL, '', '', ''),
(6, 7, '', '2022-05-11 18:09:53', '2022-05-11 19:41:10', NULL, '', '', ''),
(7, 6, '', '2022-05-11 18:14:54', '2022-05-11 18:14:54', NULL, '', '', '');

-- --------------------------------------------------------

--
-- Table structure for table `questions`
--

CREATE TABLE `questions` (
  `id` int(11) UNSIGNED NOT NULL,
  `pageID` int(11) UNSIGNED NOT NULL,
  `file` varchar(100) NOT NULL,
  `url` varchar(100) NOT NULL,
  `answer` varchar(1000) NOT NULL,
  `rightAnswers` int(11) UNSIGNED DEFAULT NULL,
  `wrongAnswers` int(11) UNSIGNED DEFAULT NULL,
  `rightAnswersRate` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `questions`
--

INSERT INTO `questions` (`id`, `pageID`, `file`, `url`, `answer`, `rightAnswers`, `wrongAnswers`, `rightAnswersRate`) VALUES
(1, 1, 'scascsa', 'sacsacsac', '3', NULL, NULL, NULL),
(2, 3, 'aaaa', 'url', 'YES', NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int(11) UNSIGNED NOT NULL,
  `nick` varchar(100) NOT NULL,
  `pass` varchar(32) NOT NULL,
  `email` varchar(200) NOT NULL,
  `status` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `nick`, `pass`, `email`, `status`) VALUES
(4, 'Akim', '123', 'akim@mail.ru', 'student'),
(5, 'Bob', '321', 'bob@mail.ru', 'student'),
(6, 'Adam', '123', 'adam@mail.ru', 'student'),
(7, 'Karl', 'Karl123', 'karl@mail.ru', 'worker'),
(8, 'Mat', 'Mat123', 'mat@mail.ru', 'student'),
(9, 'Pete', 'Pete123', 'pete@mail.ru', 'student'),
(12, 'Alex', 'Alex123', 'alex@mail.ru', 'worker'),
(13, 'Fred', '123', 'fred@mail.ru', 'student');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `page`
--
ALTER TABLE `page`
  ADD UNIQUE KEY `id` (`id`),
  ADD KEY `userID` (`userID`);

--
-- Indexes for table `questions`
--
ALTER TABLE `questions`
  ADD UNIQUE KEY `id` (`id`),
  ADD KEY `blockID` (`pageID`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD UNIQUE KEY `id` (`id`),
  ADD UNIQUE KEY `id_2` (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `page`
--
ALTER TABLE `page`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `questions`
--
ALTER TABLE `questions`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `page`
--
ALTER TABLE `page`
  ADD CONSTRAINT `page_ibfk_1` FOREIGN KEY (`userID`) REFERENCES `users` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `questions`
--
ALTER TABLE `questions`
  ADD CONSTRAINT `questions_ibfk_1` FOREIGN KEY (`pageID`) REFERENCES `page` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
