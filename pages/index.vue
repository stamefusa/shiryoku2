<template>
  <section>
    <li><b-button size="is-large" @click="clickMe('a')">0.1</b-button></li>
    <li><b-button size="is-large" @click="clickMe('b')">0.5</b-button></li>
    <li><b-button size="is-large" @click="clickMe('c')">1.0</b-button></li>
    <li><b-button size="is-large" @click="clickMe('d')">2.0</b-button></li>
  </section>
</template>

<script>
export default{
  methods: {
    async clickMe(value) {
      this.$buefy.notification.open('Recognized- started.' + value)
      if (['a', 'b', 'c', 'd'].indexOf(value) != -1) {
        this.$axios.$get('http://localhost:8080/api/'+value);
      }

      const SpeechRecognition =
        window.webkitSpeechRecognition || window.SpeechRecognition
      const recognition = new SpeechRecognition()

      recognition.onresult = (e) => {
        const input = e.results[0][0].transcript
        this.$buefy.notification.open(input)

        if (input == "上") {
          this.$axios.$get('http://localhost:8080/api/0')
        } else if (input == "右上") {
          this.$axios.$get('http://localhost:8080/api/1')
        } else if (input == "右") {
          this.$axios.$get('http://localhost:8080/api/2')
        } else if (input == "右下") {
          this.$axios.$get('http://localhost:8080/api/3')
        } else if (input == "下") {
          this.$axios.$get('http://localhost:8080/api/4')
        } else if (input == "左下") {
          this.$axios.$get('http://localhost:8080/api/5')
        } else if (input == "左") {
          this.$axios.$get('http://localhost:8080/api/6')
        } else if (input == "左上") {
          this.$axios.$get('http://localhost:8080/api/7')
        }
      }

      recognition.onend = (e) => {
        this.$buefy.notification.open('Recognized ended.')
      }

      recognition.start()
    },
  },
}
</script>

<style>
  li {
    list-style: none;
  }
</style>