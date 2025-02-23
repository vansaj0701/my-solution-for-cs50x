import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    portfolio = db.execute(
        "SELECT symbol, SUM(shares) AS shares, price, SUM(shares) * price AS total FROM portfolio WHERE user_id = ? GROUP BY symbol", user_id)
    total_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    return render_template("index.html", portfolio=portfolio, total_cash=total_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        user_id = session["user_id"]
        balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        balance = float(balance)

        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Symbol not provided")

        quote = lookup(symbol.upper())
        if quote == None:
            return apology("Incorrect symbol")

        shares = request.form.get("shares")
        if not shares:
            return apology("Shares not provided", 400)

        if not shares.isnumeric():
            return apology("Invalid Value", 400)

        shares = float(shares)

        current_price = float(quote["price"])
        price = shares * current_price

        if balance < price:
            return apology("Insufficient balance")

        remaining_balance = balance - price

        db.execute("UPDATE users SET cash = ? WHERE id = ?", remaining_balance, user_id)

        db.execute("INSERT INTO portfolio (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   user_id, quote["symbol"], shares, int(quote["price"]))

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    portfolio = db.execute("SELECT * FROM portfolio WHERE user_id = ?", user_id)

    return render_template("history.html", portfolio=portfolio)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Symbol not provided")

        quote = lookup(symbol.upper())

        if quote == None:
            return apology("Invalid symbol")

        return render_template("quote.html", name=quote["name"], price=usd(quote["price"]), symbol=quote["symbol"])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return apology("Username not provided")

        password = request.form.get("password")
        if not password:
            return apology("Password not provided")

        confirm_password = request.form.get("confirmation")
        if not confirm_password:
            return apology("Confirm password not provided")

        if password != confirm_password:
            return apology("Password doesn't match")

        hash = generate_password_hash(password)

        try:
            new_user = db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except:
            return apology("Username already exists")
        session["user_id"] = new_user

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Symbol not provided")

        shares = request.form.get("shares")
        if not shares:
            return apology("Shares not provided")
        shares = float(shares)

        quote = lookup(symbol.upper())

        if quote == None:
            return apology("Invalid symbol")

        if shares < 0:
            return apology("Invalid value")

        price = shares * quote["price"]

        user_id = session["user_id"]

        avail_balance = int(db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"])
        avail_shares = db.execute(
            "SELECT SUM(shares) as shares FROM portfolio WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)[0]["shares"]

        if shares > avail_shares:
            return apology("Insufficient Shares")

        balance = avail_balance + price

        db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, user_id)
        db.execute("INSERT INTO portfolio (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   user_id, quote["symbol"], (-1)*shares, quote["price"])

        return redirect("/")

    else:
        user_id = session["user_id"]
        symbols = db.execute(
            "SELECT symbol FROM portfolio WHERE user_id = ? GROUP BY symbol", user_id)
        return render_template("sell.html", symbols=[symbol["symbol"] for symbol in symbols])
