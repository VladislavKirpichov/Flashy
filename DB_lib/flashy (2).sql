-- phpMyAdmin SQL Dump
-- version 4.9.5
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: May 27, 2022 at 06:04 PM
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
  `theme` varchar(100) NOT NULL,
  `title` varchar(100) NOT NULL,
  `createdTime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updatedTime` timestamp NULL DEFAULT NULL,
  `lastVisited` timestamp NULL DEFAULT NULL,
  `file` varchar(96) CHARACTER SET utf8mb4 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `page`
--

INSERT INTO `page` (`id`, `userID`, `theme`, `title`, `createdTime`, `updatedTime`, `lastVisited`, `file`) VALUES
(1, 4, '', 'Диффуры', '2022-05-11 16:06:47', '2022-05-25 15:53:41', NULL, 'sss'),
(2, 5, '', '', '2022-05-11 16:48:31', NULL, NULL, ''),
(3, 4, '', 'Алгосы', '2022-05-11 16:48:48', NULL, NULL, ''),
(5, 7, '', '', '2022-05-11 18:08:52', NULL, NULL, ''),
(6, 7, '', '', '2022-05-11 18:09:53', '2022-05-11 19:41:10', NULL, ''),
(7, 6, '', '', '2022-05-11 18:14:54', '2022-05-11 18:14:54', NULL, '');

-- --------------------------------------------------------

--
-- Table structure for table `questions`
--

CREATE TABLE `questions` (
  `id` int(11) UNSIGNED NOT NULL,
  `pageID` int(11) UNSIGNED NOT NULL,
  `file` varchar(100) NOT NULL,
  `answer` varchar(1000) NOT NULL,
  `rightAnswers` int(11) UNSIGNED DEFAULT '0',
  `wrongAnswers` int(11) UNSIGNED DEFAULT '0',
  `mark` int(1) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `questions`
--

INSERT INTO `questions` (`id`, `pageID`, `file`, `answer`, `rightAnswers`, `wrongAnswers`, `mark`) VALUES
(1, 1, 'scascsa', '3', 1, 1, 0),
(2, 1, 'aaaa', 'YES', 2, 2, 0),
(3, 1, 'bbbb', '5', 0, 0, 0),
(4, 5, 'vvvv', '4', 0, 0, 0),
(5, 3, 'ttt', '7', 0, 0, 0),
(6, 3, 'rrr', '9', 0, 0, 0),
(7, 2, 'ooo', '4', 0, 0, 0),
(8, 6, 'pppp', '1', 0, 0, 0),
(9, 7, 'eeee', '5', 0, 0, 0),
(10, 2, 'qqqq', '7', 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `recommend_questions`
--

CREATE TABLE `recommend_questions` (
  `page_ID` int(11) UNSIGNED NOT NULL,
  `rec_question_1_id` int(11) UNSIGNED DEFAULT NULL,
  `mark_1` int(1) NOT NULL DEFAULT '0',
  `rec_question_2_id` int(11) UNSIGNED DEFAULT NULL,
  `mark_2` int(1) NOT NULL DEFAULT '0',
  `rec_question_3_id` int(11) UNSIGNED DEFAULT NULL,
  `mark_3` int(1) NOT NULL DEFAULT '0',
  `rec_question_4_id` int(11) UNSIGNED DEFAULT NULL,
  `mark_4` int(1) NOT NULL DEFAULT '0',
  `rec_question_5_id` int(11) UNSIGNED DEFAULT NULL,
  `mark_5` int(1) NOT NULL DEFAULT '0',
  `rec_question_6_id` int(11) UNSIGNED DEFAULT NULL,
  `mark_6` int(1) NOT NULL DEFAULT '0',
  `rec_question_7_id` int(11) UNSIGNED DEFAULT NULL,
  `mark_7` int(1) NOT NULL DEFAULT '0',
  `rec_question_8_id` int(11) UNSIGNED DEFAULT NULL,
  `mark_8` int(1) NOT NULL DEFAULT '0',
  `rec_question_9_id` int(11) UNSIGNED DEFAULT NULL,
  `mark_9` int(1) NOT NULL DEFAULT '0',
  `rec_question_10_id` int(11) UNSIGNED DEFAULT NULL,
  `mark_10` int(1) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `recommend_questions`
--

INSERT INTO `recommend_questions` (`page_ID`, `rec_question_1_id`, `mark_1`, `rec_question_2_id`, `mark_2`, `rec_question_3_id`, `mark_3`, `rec_question_4_id`, `mark_4`, `rec_question_5_id`, `mark_5`, `rec_question_6_id`, `mark_6`, `rec_question_7_id`, `mark_7`, `rec_question_8_id`, `mark_8`, `rec_question_9_id`, `mark_9`, `rec_question_10_id`, `mark_10`) VALUES
(1, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8, 0, 9, 0, 10, 0);

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int(11) UNSIGNED NOT NULL,
  `nick` varchar(30) NOT NULL,
  `name` varchar(100) NOT NULL,
  `pass` varchar(32) NOT NULL,
  `email` varchar(200) NOT NULL,
  `status` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `nick`, `name`, `pass`, `email`, `status`) VALUES
(4, 'Akim', '', '123', 'akim@mail.ru', 'student'),
(5, 'Bob', '', '321', 'new_email', 'student'),
(6, 'Adam', '', '123', 'adam@mail.ru', 'student'),
(7, 'Karl', '', 'Karl123', 'karl@mail.ru', 'worker'),
(8, 'Mat', '', 'Mat123', 'mat@mail.ru', 'student'),
(9, 'Pete', '', 'Pete123', 'pete@mail.ru', 'student'),
(12, 'Alex', '', 'Alex123', 'alex@mail.ru', 'worker'),
(13, 'Fred', '', '123', 'fred@mail.ru', 'worker');

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
-- Indexes for table `recommend_questions`
--
ALTER TABLE `recommend_questions`
  ADD UNIQUE KEY `id` (`page_ID`),
  ADD UNIQUE KEY `id_q_10` (`rec_question_10_id`),
  ADD UNIQUE KEY `id_q_9` (`rec_question_9_id`),
  ADD UNIQUE KEY `id_q_8` (`rec_question_8_id`),
  ADD UNIQUE KEY `id_q_7` (`rec_question_7_id`),
  ADD UNIQUE KEY `id_q_6` (`rec_question_6_id`),
  ADD UNIQUE KEY `id_q_5` (`rec_question_5_id`),
  ADD UNIQUE KEY `id_q_4` (`rec_question_4_id`),
  ADD UNIQUE KEY `id_q_3` (`rec_question_3_id`),
  ADD UNIQUE KEY `q_id_2` (`rec_question_2_id`),
  ADD UNIQUE KEY `q_id_1` (`rec_question_1_id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD UNIQUE KEY `id` (`id`),
  ADD UNIQUE KEY `nick` (`nick`);

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
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

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

--
-- Constraints for table `recommend_questions`
--
ALTER TABLE `recommend_questions`
  ADD CONSTRAINT `recommend_questions_ibfk_1` FOREIGN KEY (`page_ID`) REFERENCES `page` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `recommend_questions_ibfk_10` FOREIGN KEY (`rec_question_9_id`) REFERENCES `questions` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `recommend_questions_ibfk_11` FOREIGN KEY (`rec_question_10_id`) REFERENCES `questions` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `recommend_questions_ibfk_2` FOREIGN KEY (`rec_question_1_id`) REFERENCES `questions` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `recommend_questions_ibfk_3` FOREIGN KEY (`rec_question_2_id`) REFERENCES `questions` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `recommend_questions_ibfk_4` FOREIGN KEY (`rec_question_3_id`) REFERENCES `questions` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `recommend_questions_ibfk_5` FOREIGN KEY (`rec_question_4_id`) REFERENCES `questions` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `recommend_questions_ibfk_6` FOREIGN KEY (`rec_question_5_id`) REFERENCES `questions` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `recommend_questions_ibfk_7` FOREIGN KEY (`rec_question_6_id`) REFERENCES `questions` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `recommend_questions_ibfk_8` FOREIGN KEY (`rec_question_7_id`) REFERENCES `questions` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `recommend_questions_ibfk_9` FOREIGN KEY (`rec_question_8_id`) REFERENCES `questions` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
