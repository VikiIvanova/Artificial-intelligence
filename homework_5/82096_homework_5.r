install.packages("dplyr")
install.packages("tidyr")
install.packages("purrr")
library(dplyr) 
library(tidyr)
library(purrr)

# laplace smoothing fot P(class) with lambda = 1 and K = 2 (two classes)
laplaceProb <- function(class) {
  (sum(train$class.name == class) + 1) / (nrow(train) + 2)
}
#conditional
# laplace smoothing fot P(attribute | class) with lambda = 1 and A = 3 (y, n, ?)
laplaceCondProb <- function(class, attribute, row) {
  (nrow(train[train[ , attribute] == test[row, attribute] & train$class.name == class, ]) + 1) / (sum(train$class.name == class) + 3)
}
#смятаме формулата и ги смятаме в логаритъм, защото ако имаме много малки вероятности стават пренибрежимо малки (произведението ми е сбора от логаритмите)
# log(P(class | test[row])) without the denominator P(test[row]) // не го смятаме защото то е едно и също през всички сметки

pClassRow <- function(class, testrow) {
  log(laplaceProb(class)) + 
    log(laplaceCondProb(class, "handicapped.infants", testrow)) +
    log(laplaceCondProb(class, "water.project.cost.sharing", testrow)) +
    log(laplaceCondProb(class, "adoption.of.the.budget.resolution", testrow)) +
    log(laplaceCondProb(class, "physician.fee.freeze", testrow)) +
    log(laplaceCondProb(class, "el.salvador.aid", testrow)) +
    log(laplaceCondProb(class, "religious.groups.in.schools", testrow)) +
    log(laplaceCondProb(class, "anti.satellite.test.ban", testrow)) +
    log(laplaceCondProb(class, "aid.to.nicaraguan.contras", testrow)) +
    log(laplaceCondProb(class, "mx.missile", testrow)) +
    log(laplaceCondProb(class, "immigration", testrow)) +
    log(laplaceCondProb(class, "synfuels.corporation.cutback", testrow)) +
    log(laplaceCondProb(class, "education.spending", testrow)) +
    log(laplaceCondProb(class, "superfund.right.to.sue", testrow)) +
    log(laplaceCondProb(class, "crime", testrow)) +
    log(laplaceCondProb(class, "duty.free.exports", testrow)) +
    log(laplaceCondProb(class, "export.administration.act.south.africa", testrow))
  
}


# load the data and assign names to the columns
house.votes <- read.csv("D:/4kurs/AI/homeworks/hom5/house-votes-84.data", header=FALSE)
colnames(house.votes) = c('class-name', 'handicapped-infants', 'water-project-cost-sharing',
                          'adoption-of-the-budget-resolution', 'physician-fee-freeze',
                          'el-salvador-aid', 'religious-groups-in-schools',
                          'anti-satellite-test-ban', 'aid-to-nicaraguan-contras',
                          'mx-missile', 'immigration', 'synfuels-corporation-cutback',
                          'education-spending', 'superfund-right-to-sue', 'crime',
                          'duty-free-exports', 'export-administration-act-south-africa')
View(house.votes)

# shuffle the data (for random groups every time) and split it in 10 groups
num_groups = 10
house.votes <- house.votes[sample(1:nrow(house.votes)), ]
sample_groups <- house.votes %>% 
  group_by((row_number()-1) %/% (n()/num_groups)) %>%
  nest %>% pull(data)

# vector of accuracies for every group
accuracies <- c()

# 10-fold cross-validation on the groups
for (testIndex in 1:num_groups) {
  # get the test and train sets
  test <- data.frame(sample_groups[testIndex])
  train <- data.frame(bind_rows(sample_groups[-testIndex]))
  
  # the results for the test group
  results = c()
  
  # test every row in the test set
  for (row in 1:nrow(test)) {
    republican <- pClassRow("republican", row)
    democrat <- pClassRow("democrat", row)
    
    result <- ifelse(republican > democrat, yes = "republican", no = "democrat")
    results <- append(results, result)
  }
  
  credibility <- results == test$class.name
  accuracies <- append(accuracies, sum(credibility) / length(credibility))
}

cat("accuracies = ", accuracies)
cat("mean accuracy = ", mean(accuracies))









