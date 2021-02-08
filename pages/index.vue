<template>
  <section>
    <b-button @click="clickMe('a')">0.1</b-button>
    <b-button @click="clickMe('0')">0.3</b-button>
    <b-button @click="clickMe('1')">0.5</b-button>
    <b-button @click="clickMe('2')">1.0</b-button>
  </section>
</template>

<script>
export default{
  methods: {
    async clickMe(value) {
      this.$buefy.notification.open('Recognized- started.' + value)
      const SpeechRecognition =
        window.webkitSpeechRecognition || window.SpeechRecognition
      const recognition = new SpeechRecognition()

      recognition.onresult = (e) => {
        const input = e.results[0][0].transcript
        this.$buefy.notification.open(input)

        if (input == "上") {
          this.$axios.$get('http://localhost:8080/api/1')
        } else if (input == "右") {
          this.$axios.$get('http://localhost:8080/api/2')
        } else if (input == "下") {
          this.$axios.$get('http://localhost:8080/api/0')
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
