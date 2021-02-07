<template>
  <section>
    <b-button @click="clickMe('a')">0.1</b-button>
    <b-button @click="clickMe('b')">0.3</b-button>
    <b-button @click="clickMe('c')">0.5</b-button>
    <b-button @click="clickMe('d')">1.0</b-button>
  </section>
</template>

<script>
export default{
  methods: {
    async clickMe(value) {
      this.$axios.$get('/api', {
        params: {value: value}
      })
      /*
      this.$buefy.notification.open('Recognized- started.' + value)
      const SpeechRecognition =
        window.webkitSpeechRecognition || window.SpeechRecognition
      const recognition = new SpeechRecognition()

      recognition.onresult = (e) => {
        const input = e.results[0][0].transcript
        this.$buefy.notification.open(input)
      }

      recognition.onend = (e) => {
        this.$buefy.notification.open('Recognized ended.')
      }

      recognition.start()
      */
    },
  },
}
</script>
