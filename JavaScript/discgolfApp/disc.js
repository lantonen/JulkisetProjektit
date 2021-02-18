class Disc {
    constructor(name, speed, glide, turn, fade, weight, color) {
        this.name = name;
        this.speed = speed;
        this.glide = glide;
        this.turn = turn;
        this.fade = fade;
        this.weight = weight;
        this.color = color;
        this.stats = [this.speed, this.glide, this.turn, this.fade]
        this.giveStats()
    }

    giveStats() {
        alert(this.stats)
    }

}