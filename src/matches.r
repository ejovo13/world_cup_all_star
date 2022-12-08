library(tidyverse)
library(pracma)

filename <- "src/WorldCupMatches.csv"

df <- as_tibble(read_csv(filename))
colnames(df)

df <- df |> select(Year, 
             home = "Home Team Name", 
             home_goals = "Home Team Goals", 
             away = "Away Team Name", 
             away_goals = "Away Team Goals") |>
             filter(!is.na(away) | !is.na(away_goals) | !is.na(home) | !is.na(home_goals))

names <- unique(c(df$home, df$away))

# Calculate the average number of goals for a given team

get_away_goals <- function(names_index) {
    sum(df$away_goals[df$away == names[names_index]])
}

get_home_wins <- function(names_index) {
    df_home_games <- df |> filter(home == names[names_index])
    nrow(df_home_games |> filter(home_goals > away_goals))
}

get_home_losses <- function(names_index) {
    df_home_games <- df |> filter(home == names[names_index])
    nrow(df_home_games |> filter(home_goals < away_goals))
}

get_home_ties <- function(names_index) {
    df_home_games <- df |> filter(home == names[names_index])
    nrow(df_home_games |> filter(home_goals == away_goals))
}

get_away_ties <- function(names_index) {
    df_away_games <- df |> filter(away == names[names_index])
    nrow(df_away_games |> filter(away_goals == home_goals))
}

get_away_wins <- function(names_index) {
    df_away_games <- df |> filter(away == names[names_index])
    nrow(df_away_games |> filter(away_goals > home_goals))
}

get_away_losses <- function(names_index) {
    df_away_games <- df |> filter(away == names[names_index])
    nrow(df_away_games |> filter(away_goals < home_goals))
}

away_scored_against <- function(names_index) {
    sum(df$home_goals[df$away == names[names_index]])
}

home_scored_against <- function(names_index) {
    sum(df$away_goals[df$home == names[names_index]])
}

get_total_scored_against <- function(names_index) {
    home_against <- home_scored_against(names_index)
    away_against <- away_scored_against(names_index)

    home_against + away_against
}

get_total_wins <- function(names_index) {

    # Count the games where the home team has more than the away team
    home_wins <- get_home_wins(names_index)
    away_wins <- get_away_wins(names_index)

    home_wins + away_wins
}

get_total_losses <- function(names_index) {

    # Filter to the matches that match this team
    df_home_games <- df |> filter(home == names[names_index])
    df_away_games <- df |> filter(home == names[names_index])

    # Count the games where the home team has more than the away team
    home_losses <- nrow(df_home_games |> filter(home_goals < away_goals))
    away_losses <- nrow(df_away_games |> filter(away_goals < home_goals))

    home_losses + away_losses
}

get_home_goals <- function(names_index) {
    sum(df$home_goals[df$home == names[names_index]])
}

get_away_goals <- function(names_index) {
    sum(df$away_goals[df$away == names[names_index]])
}

get_away_games <- function(names_index) {
    sum(df$away == names[names_index])
}

get_home_games <- function(names_index) {
    sum(df$home == names[names_index])
}

# get the sum of the home and away goals 
get_total_goals <- function(names_index) {
    away_goals <- get_away_goals(names_index)
    home_goals <- get_home_goals(names_index)
    away_goals + home_goals
}

get_total_ties <- function(names_index) {
    away_ties <- get_away_ties(names_index)
    home_ties <- get_home_ties(names_index) 
    away_ties + home_ties    
}

get_total_games <- function(names_index) {
    away_games <- get_away_games(names_index)
    home_games <- get_home_games(names_index)
    away_games + home_games
}

avg_goals <- function(names_index) {
    total_goals <- get_total_goals(names_index)
    total_games <- get_total_games(names_index)
    total_goals / total_games
}

# Now we can store the number of home games and the number of away games

indices <- 1:length(names)

# total_goals
total_games <- map_dbl(indices, get_total_games)
total_wins <- map_dbl(indices, get_total_wins)
total_losses <- map_dbl(indices, get_total_losses)
home_goals <- map_dbl(indices, get_home_goals)
home_games <- map_dbl(indices, get_home_games)
home_wins <- map_dbl(indices, get_home_wins)
away_wins <- map_dbl(indices, get_away_wins)
away_goals <- map_dbl(indices, get_away_goals)
away_games <- map_dbl(indices, get_away_games)
win_rate <- total_wins / total_games
away_ties <- map_dbl(indices, get_away_ties)
home_ties <- map_dbl(indices, get_home_ties)
total_ties <- away_ties + home_ties


# df_clean <- tibble(names, total_goals, total_games, total_wins, total_losses, total_ties, win_rate, home_goals, home_games, away_goals, away_games, win_rate)

df_home <- tibble(names, 
                  games = home_games, 
                  wins = home_wins,
                  losses = map_dbl(indices, get_home_losses),
                  ties = home_ties,
                  goals = home_goals, 
                  against = map_dbl(indices, home_scored_against))


df_away <- tibble(names, 
                  games = away_games, 
                  wins = away_wins,
                  losses = map_dbl(indices, get_away_losses),
                  ties = away_ties,
                  goals = away_goals, 
                  against = map_dbl(indices, away_scored_against))

df_total <- tibble(names,
                   games = total_games,
                   wins = total_wins,
                   losses = total_losses,
                   ties = map_dbl(indices, get_total_ties),
                   goals = map_dbl(indices, get_total_goals),
                   against = map_dbl(indices, get_total_scored_against))

df_home <- df_home |> mutate(win_rate = wins / games, avg_goals = goals / games)
df_away <- df_away |> mutate(win_rate = wins / games, avg_goals = goals / games)
df_total <- df_total |> mutate(win_rate = wins / games, avg_goals = goals / games)

types <- c("bot", "mid", "top")
cutoffs <- c(0, 0.25, 0.5, 1.0)

count_type <- function(df, index) {
    t <- types[index]
    cut_hi <- cutoffs[index + 1]
    cut_lo <- cutoffs[index]

    cond_a <- df$win_rate < cut_hi
    cond_b <- df$win_rate >= cut_lo
    cond_c <- !is.na(df$win_rate)
    sum(cond_a & cond_b & cond_c)
}

home_counts <- map_dbl(1:3, function(i) { count_type(df_home, i) })
away_counts <- map_dbl(1:3, function(i) { count_type(df_away, i) })


new_names_home <- map_chr(colnames(df_home), function(s) { paste("home", s, sep="_")})
new_names_home[1] <- "names"
new_names_away <- map_chr(colnames(df_away), function(s) { paste("away", s, sep="_")})

colnames(df_home) <- new_names_home
colnames(df_away) <- new_names_away

df_away_no_name <- df_away |> select(c(2:ncol(df_away)))
df_full <- bind_cols(df_home, df_away |> select(c(2:ncol(df_away))))

write_csv(df_full, "world_cup_stats.csv")

# We only accept the top 48 teams 
# avg_home_goals <- df_home$goals / df$
